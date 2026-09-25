#include "RegionShadowRenderer.h"

#include "ShadowRenderUtils.h"

#include "config/Config.h"
#include "data/BlockColor.h"
#include "data/BlockDataBase.h"
#include "data/cache/MapCacheManager.h"
#include "data/cache/WorldMapCacheManager.h"
#include "data/pos/ChunkPosWithDim.h"
#include "data/pos/ChunkWorldPos.h"
#include "data/pos/RegionChunkPos.h"
#include "data/pos/WorldPos.h"


#include <algorithm>
#include <array>
#include <cmath>
#include <memory>
#include <mutex>
#include <optional>
#include <shared_mutex>
#include <vector>

namespace map_demo {

void RegionShadowRenderer::bake(const std::shared_ptr<RegionCacheData>& data) {
    if (!data) return;

    std::uint32_t dirtyEpochSnapshot[16][16]{};

    // Snapshot raw data under lock, then bake offline without holding the lock
    for (int regionChunkZ = 0; regionChunkZ < 16; regionChunkZ++) {
        for (int regionChunkX = 0; regionChunkX < 16; regionChunkX++) {
            auto chunkData = data->getChunkData(RegionChunkPos(regionChunkX, regionChunkZ));
            if (!chunkData || !chunkData->loadChunkBaseData) continue;
            std::shared_lock<std::shared_mutex> lock(chunkData->mutex_);
            handlingRegion[regionChunkZ][regionChunkX]   = std::make_shared<ShadowRenderChunkData>(*chunkData);
            dirtyEpochSnapshot[regionChunkZ][regionChunkX] = chunkData->bakedDirtyEpoch;
        }
    }

    auto& cfg = config::getConfig().terrain.shadow;
    if (cfg.transparentWater) applyWaterOverlay();

    heightQueryCount = 0;
    heightQueryMiss  = 0;

    if (cfg.renderStyle == 1) {
        applyStyle1();
    } else if (cfg.renderStyle == 2) {
        applyStyle2();
    }

    // bake 结束、写回之前：把 bake 结果写入大地图 region 缓存（当前为 bake 工作线程，缓存内部加锁）
    WorldMapCacheManager::getInstance().updateFromRegionBake(handlingRegionPos, handlingRegion);

    bool keptDirty = false;
    for (int regionChunkZ = 0; regionChunkZ < 16; regionChunkZ++) {
        for (int regionChunkX = 0; regionChunkX < 16; regionChunkX++) {
            auto shadowChunkData = handlingRegion[regionChunkZ][regionChunkX];
            if (!shadowChunkData) continue;
            auto chunkData = data->getChunkData(RegionChunkPos(regionChunkX, regionChunkZ));
            std::unique_lock<std::shared_mutex> lock(chunkData->mutex_);
            for (int chunkWorldZ = 0; chunkWorldZ < 16; chunkWorldZ++) {
                for (int chunkWorldX = 0; chunkWorldX < 16; chunkWorldX++) {
                    auto& blockData            = chunkData->blocksData[chunkWorldZ][chunkWorldX];
                    auto& shadowBlockData      = shadowChunkData->blocksData[chunkWorldZ][chunkWorldX];
                    blockData.bakedColor       = shadowBlockData.color;
                    blockData.shadowOriginData = std::move(shadowBlockData.shadowOriginData);
                }
            }
            chunkData->shadowScale = shadowChunkData->shadowScale;
            // region bake 已覆盖该 chunk，清除其 chunk 级脏标记（已持有 unique_lock，直接赋值）；
            // 但 bake 期间被重新标脏（epoch 变化）的 chunk 必须保留脏标记，否则阴影残留
            if (chunkData->bakedDirtyEpoch == dirtyEpochSnapshot[regionChunkZ][regionChunkX]) {
                chunkData->bakedDirty = false;
            } else {
                keptDirty = true;
            }
        }
    }

    // 有 chunk 在 bake 期间被重新标脏：重新武装 region 防抖，保证脏 chunk 会被重新调度
    if (keptDirty) data->markBakedDirty();
}

// Style 1: simple heightmap gradient shadow, light from northwest
void RegionShadowRenderer::applyStyle1() {
    auto& cfg   = config::getConfig().terrain.shadow;
    int   level = cfg.shadowLevel;
    if (level <= 0) level = 100;

    int dimId = handlingRegionPos.dimId;

    for (int regionChunkZ = 0; regionChunkZ < 16; regionChunkZ++) {
        auto westChunk = getChunk(ChunkPosWithDim(-1, regionChunkZ, dimId));
        for (int regionChunkX = 0; regionChunkX < 16; regionChunkX++) {
            // if (!hasData(x, z)) continue;
            auto shadowChunkData = handlingRegion[regionChunkZ][regionChunkX];
            if (!shadowChunkData) {
                westChunk = shadowChunkData;
                continue;
            }
            auto northChunk = getChunk(ChunkPosWithDim(regionChunkX, regionChunkZ - 1, dimId));
            for (int chunkWorldZ = 0; chunkWorldZ < 16; chunkWorldZ++) {
                for (int chunkWorldX = 0; chunkWorldX < 16; chunkWorldX++) {
                    auto& blockInfo = shadowChunkData->blocksData[chunkWorldZ][chunkWorldX];
                    auto  cur       = blockInfo.height;
                    int   sum       = 0;
                    if (!chunkWorldX) {
                        if (!westChunk) sum += cur;
                        else sum += westChunk->getBlockBaseData(ChunkWorldPos(15, chunkWorldZ)).height;
                    }
                    if (!chunkWorldZ) {
                        if (!northChunk) sum += cur;
                        else sum += northChunk->getBlockBaseData(ChunkWorldPos(chunkWorldX, 15)).height;
                    }
                    BlockColor& c = blockInfo.color;
                    if (cur * 2 > sum) {
                        c = BlockColor{
                            static_cast<std::uint8_t>(clamp255(c.r * level / 100)),
                            static_cast<std::uint8_t>(clamp255(c.g * level / 100)),
                            static_cast<std::uint8_t>(clamp255(c.b * level / 100)),
                            c.a
                        };
                    } else if (cur * 2 < sum) {
                        c = BlockColor{
                            static_cast<std::uint8_t>(clamp255(c.r * 100 / level)),
                            static_cast<std::uint8_t>(clamp255(c.g * 100 / level)),
                            static_cast<std::uint8_t>(clamp255(c.b * 100 / level)),
                            c.a
                        };
                    }
                }
            }
            westChunk = shadowChunkData;
        }
    }
}

void RegionShadowRenderer::applyWaterOverlay() {
    // for (int z = 0; z < ShadowRegion::SIZE; ++z) {
    //     for (int x = 0; x < ShadowRegion::SIZE; ++x) {
    //         const auto& info = getInfo(x, z);
    //         if (info.waterDepth == 0) continue;

    //         float opacity = std::min(0.15f * static_cast<float>(info.waterDepth), 0.85f);
    //         setPixel(x, z, blendColors(getPixel(x, z), info.waterSurfaceColor, opacity));
    //     }
    // }
}

void RegionShadowRenderer::applyShadowMap(int scale) {
    auto& cfg = config::getConfig().terrain.shadow;

    constexpr float kShadowDarkness = 0.52f;
    constexpr int   kMaxSteps       = 96;

    const float deg2rad     = 3.1415926535f / 180.0f;
    const float azimuth_rad = cfg.lightAzimuth * deg2rad;
    const float zenith_rad  = cfg.lightZenith * deg2rad;

    const float sunX     = std::sin(azimuth_rad) * std::cos(zenith_rad);
    const float sunY     = std::sin(zenith_rad);
    const float sunZ     = -std::cos(azimuth_rad) * std::cos(zenith_rad);
    const float sun2dLen = std::sqrt(sunX * sunX + sunZ * sunZ);
    if (sun2dLen < 0.0001f) return;

    const float sdx       = sunX / sun2dLen;
    const float sdz       = sunZ / sun2dLen;
    const float dzPerStep = sunY / sun2dLen;

    int dimId = handlingRegionPos.dimId;

    int maxY = 0;
    if (!dimId) maxY = 320;
    else if (dimId == 1) maxY = 128;
    else if (dimId == 2) maxY = 256;

    if (sunX <= 0 && sunZ <= 0) {
        for (int chunkZ = 0; chunkZ < 16; chunkZ++) {
            auto westChunk      = getChunkWithEffectiveShadowData(ChunkPosWithDim{-1, chunkZ, dimId}, scale);
            auto northWestChunk = getChunkWithEffectiveShadowData(ChunkPosWithDim{-1, chunkZ - 1, dimId}, scale);
            for (int chunkX = 0; chunkX < 16; chunkX++) {
                auto chunk = handlingRegion[chunkZ][chunkX];
                if (!chunk) {
                    westChunk      = chunk;
                    northWestChunk = getChunkWithEffectiveShadowData(ChunkPosWithDim{chunkX, chunkZ - 1, dimId}, scale);
                    continue;
                }
                auto northChunk = getChunkWithEffectiveShadowData(ChunkPosWithDim{chunkX, chunkZ - 1, dimId}, scale);
                for (int blockZ = 0; blockZ < 16; blockZ++) {
                    const BlockDataBase* westBlock = nullptr;
                    if (westChunk) westBlock = &westChunk->getBlockBaseData(ChunkWorldPos{15, blockZ});
                    const BlockDataBase* northWestBlock = nullptr;
                    if (!blockZ) {
                        if (northWestChunk) northWestBlock = &northWestChunk->getBlockBaseData(ChunkWorldPos{15, 15});
                    } else if (westChunk) northWestBlock = &westChunk->getBlockBaseData(ChunkWorldPos{15, blockZ - 1});
                    for (int blockX = 0; blockX < 16; blockX++) {
                        auto& shadowOriginData = chunk->blocksData[blockZ][blockX].shadowOriginData;
                        shadowOriginData.assign(scale, std::vector<float>(scale, 0.0f));
                        auto&                handlingBlockData = chunk->getBlockData(ChunkWorldPos(blockX, blockZ));
                        const BlockDataBase* northBlock        = nullptr;
                        if (!blockZ) {
                            if (northChunk) northBlock = &northChunk->getBlockBaseData(ChunkWorldPos{blockX, 15});
                        } else northBlock = &chunk->getBlockBaseData(ChunkWorldPos{blockX, blockZ - 1});
                        bool canSkip = (!westBlock || handlingBlockData.height >= westBlock->height)
                                    && (!northBlock || handlingBlockData.height >= northBlock->height)
                                    && (!northWestBlock || handlingBlockData.height >= northWestBlock->height);
                        int h = handlingBlockData.height;

                        for (int scaleZ = 0; scaleZ < scale; scaleZ++) {
                            float westShadowData = 0.0f;
                            if (westBlock) westShadowData = westBlock->shadowOriginData[scaleZ][scale - 1];
                            float northWestShadowData = 0.0f;
                            if (!scaleZ) {
                                if (northWestBlock)
                                    northWestShadowData = northWestBlock->shadowOriginData[scale - 1][scale - 1];
                            } else if (westBlock)
                                northWestShadowData = westBlock->shadowOriginData[scaleZ - 1][scale - 1];
                            for (int scaleX = 0; scaleX < scale; scaleX++) {
                                // auto currentShadowData = handlingBlockData.shadowOriginData[scaleZ][scaleX];
                                float northShadowData = 0.0f;
                                if (!scaleZ) {
                                    if (northBlock) northShadowData = northBlock->shadowOriginData[scale - 1][scaleX];
                                } else northShadowData = handlingBlockData.shadowOriginData[scaleZ - 1][scaleX];
                                if (canSkip && westShadowData < 0.0001f && northShadowData < 0.0001f
                                    && northWestShadowData < 0.0001f) {
                                    handlingBlockData.shadowOriginData[scaleZ][scaleX] = 0.0f;
                                    continue;
                                }

                                float offsetX = static_cast<float>(chunkX * 16 + blockX)
                                              + (static_cast<float>(scaleX) + 0.5f) / static_cast<float>(scale);
                                float offsetZ = static_cast<float>(chunkZ * 16 + blockZ)
                                              + (static_cast<float>(scaleZ) + 0.5f) / static_cast<float>(scale);
                                auto lastOffsetPos = WorldPos{0x7fffffff, 0x7fffffff, dimId};
                                for (int s = 1; s <= kMaxSteps; ++s) {
                                    // 负坐标下 static_cast<int> 会向零截断，必须用 floor 保证采样到正确方块
                                    int sx = static_cast<int>(std::floor(offsetX + static_cast<float>(s) * sdx));
                                    int sz = static_cast<int>(std::floor(offsetZ + static_cast<float>(s) * sdz));
                                    if (sx != lastOffsetPos.x || sz != lastOffsetPos.z) {
                                        lastOffsetPos.x = sx;
                                        lastOffsetPos.z = sz;
                                        int currentHeight =
                                            h + static_cast<int>(static_cast<float>(s) * dzPerStep + 0.01f);
                                        int sampleHeight = getHeight(lastOffsetPos);
                                        if (sampleHeight > currentHeight) {
                                            handlingBlockData.shadowOriginData[scaleZ][scaleX] = kShadowDarkness;
                                            break;
                                        } else if (currentHeight > maxY) {
                                            break;
                                        }
                                    }
                                }
                                westShadowData      = handlingBlockData.shadowOriginData[scaleZ][scaleX];
                                northWestShadowData = northShadowData;
                            }
                        }
                        westBlock      = &handlingBlockData;
                        northWestBlock = northBlock;
                    }
                }
                chunk->shadowScale = scale;
                westChunk          = chunk;
                northWestChunk     = northChunk;
            }
        }
    } else {
        for (int chunkZ = 0; chunkZ < 16; chunkZ++) {
            for (int chunkX = 0; chunkX < 16; chunkX++) {
                auto chunk = handlingRegion[chunkZ][chunkX];
                if (!chunk) continue;
                for (int blockZ = 0; blockZ < 16; blockZ++) {
                    for (int blockX = 0; blockX < 16; blockX++) {
                        auto& shadowOriginData = chunk->blocksData[blockZ][blockX].shadowOriginData;
                        shadowOriginData.assign(scale, std::vector<float>(scale, 0.0f));
                        auto& handlingBlockData =
                            handlingRegion[chunkZ][chunkX]->getBlockData(ChunkWorldPos(blockX, blockZ));
                        int h = handlingBlockData.height;

                        for (int scaleZ = 0; scaleZ < scale; scaleZ++) {
                            for (int scaleX = 0; scaleX < scale; scaleX++) {
                                float offsetX = static_cast<float>(chunkX * 16 + blockX)
                                              + (static_cast<float>(scaleX) + 0.5f) / static_cast<float>(scale);
                                float offsetZ = static_cast<float>(chunkZ * 16 + blockZ)
                                              + (static_cast<float>(scaleZ) + 0.5f) / static_cast<float>(scale);
                                auto lastOffsetPos = WorldPos{0x7fffffff, 0x7fffffff, dimId};
                                for (int s = 1; s <= kMaxSteps * scale; ++s) {
                                    // 负坐标下 static_cast<int> 会向零截断，必须用 floor 保证采样到正确方块
                                    int sx = static_cast<int>(std::floor(offsetX + static_cast<float>(s) * sdx));
                                    int sz = static_cast<int>(std::floor(offsetZ + static_cast<float>(s) * sdz));
                                    if (sx != lastOffsetPos.x || sz != lastOffsetPos.z) {
                                        lastOffsetPos.x = sx;
                                        lastOffsetPos.z = sz;
                                        int currentHeight =
                                            h + static_cast<int>(static_cast<float>(s) * dzPerStep + 0.01f);
                                        int sampleHeight = getHeight(lastOffsetPos);
                                        if (sampleHeight > currentHeight) {
                                            handlingBlockData.shadowOriginData[scaleZ][scaleX] = kShadowDarkness;
                                            break;
                                        } else if (currentHeight > maxY) {
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                chunk->shadowScale = scale;
            }
        }
    }

    const int pcfRadius = std::clamp(cfg.pcfRadius, 0, 8);

    if (pcfRadius) {
        std::array<std::vector<std::vector<float>>, 16>                 northShadowData;
        std::array<std::vector<std::vector<float>>, 16>                 southShadowData;
        std::array<std::array<std::vector<std::vector<float>>, 16>, 16> shadowTempData;
        std::shared_ptr<const ChunkDataBase>                            westChunk     = nullptr;
        std::shared_ptr<const ChunkDataBase>                            handlingChunk = nullptr;
        std::shared_ptr<const ChunkDataBase>                            eastChunk     = nullptr;

        auto getShadowData = [&westChunk, &handlingChunk, &eastChunk, &scale](int sx, int sz) -> std::optional<float> {
            if (sx < 0) {
                if (!westChunk) return std::nullopt;
                return westChunk->getBlockBaseData(ChunkWorldPos{(sx + 16 * scale) / scale, sz / scale})
                    .shadowOriginData[sz % scale][(sx + 16 * scale) % scale];
            } else if (sx < 16 * scale) {
                if (!handlingChunk) return std::nullopt;
                return handlingChunk->getBlockBaseData(ChunkWorldPos{sx / scale, sz / scale})
                    .shadowOriginData[sz % scale][sx % scale];
            } else {
                if (!eastChunk) return std::nullopt;
                return eastChunk->getBlockBaseData(ChunkWorldPos{sx / scale - 16, sz / scale})
                    .shadowOriginData[sz % scale][sx % scale];
            }
        };

        for (int chunkZ = -1; chunkZ <= 16; chunkZ++) {
            westChunk     = getChunkWithEffectiveShadowData(ChunkPosWithDim{-1, chunkZ, dimId}, scale);
            handlingChunk = getChunkWithEffectiveShadowData(ChunkPosWithDim{0, chunkZ, dimId}, scale);
            for (int chunkX = 0; chunkX < 16; chunkX++) {
                eastChunk = getChunkWithEffectiveShadowData(ChunkPosWithDim{chunkX + 1, chunkZ, dimId}, scale);
                std::vector<std::vector<float>>* handlingChunkShadowData = nullptr;
                if (chunkZ == -1) handlingChunkShadowData = &northShadowData[chunkX];
                else if (chunkZ == 16) handlingChunkShadowData = &southShadowData[chunkX];
                else handlingChunkShadowData = &shadowTempData[chunkZ][chunkX];
                int zSize;
                if (chunkZ == -1 || chunkZ == 16) zSize = pcfRadius;
                else zSize = 16 * scale;
                handlingChunkShadowData->resize(zSize);
                if (!westChunk && !handlingChunk && !eastChunk) {
                    for (int sZ = 0; sZ < zSize; sZ++) {
                        (*handlingChunkShadowData)[sZ].resize(16 * scale, 0.0f);
                        for (int sX = 0; sX < 16 * scale; sX++) {
                            (*handlingChunkShadowData)[sZ][sX] = 0.0f;
                        }
                    }
                } else {
                    for (int sZ = 0; sZ < zSize; sZ++) {
                        (*handlingChunkShadowData)[sZ].resize(16 * scale, 0.0f);
                        for (int sX = 0; sX < 16 * scale; sX++) {
                            float sum   = 0.0f;
                            int   count = 0;
                            for (int index = sX - pcfRadius; index <= sX + pcfRadius; index++) {
                                std::optional<float> shadowData{};
                                if (chunkZ == -1) shadowData = getShadowData(index, 16 * scale - pcfRadius + sZ);
                                else shadowData = getShadowData(index, sZ);
                                if (shadowData) {
                                    sum += shadowData.value();
                                    count++;
                                }
                            }
                            if (count) (*handlingChunkShadowData)[sZ][sX] = sum / static_cast<float>(count);
                            else (*handlingChunkShadowData)[sZ][sX] = 0.0f;
                        }
                    }
                }
                westChunk     = handlingChunk;
                handlingChunk = eastChunk;
            }
        }

        std::vector<std::vector<float>>* northChunkShadowData;
        std::vector<std::vector<float>>* handlingChunkShadowData;
        std::vector<std::vector<float>>* southChunkShadowData;
        auto                             getShadowData2 =
            [&northChunkShadowData, &handlingChunkShadowData, &southChunkShadowData, &scale](int sx, int sz) {
                if (sz < 0) return (*northChunkShadowData)[northChunkShadowData->size() + sz][sx];
                else if (sz < 16 * scale) return (*handlingChunkShadowData)[sz][sx];
                else return (*southChunkShadowData)[sz - 16 * scale][sx];
            };
        for (int chunkX = 0; chunkX < 16; chunkX++) {
            northChunkShadowData    = &northShadowData[chunkX];
            handlingChunkShadowData = &shadowTempData[0][chunkX];
            for (int chunkZ = 0; chunkZ < 16; chunkZ++) {
                if (chunkZ < 15) southChunkShadowData = &shadowTempData[chunkZ + 1][chunkX];
                else southChunkShadowData = &southShadowData[chunkX];
                auto shadowChunk = handlingRegion[chunkZ][chunkX];
                if (!shadowChunk) continue;
                for (int blockZ = 0; blockZ < 16; blockZ++) {
                    for (int blockX = 0; blockX < 16; blockX++) {
                        auto& handlingBlock = shadowChunk->blocksData[blockZ][blockX];
                        float sum           = 0.0f;
                        for (int scaleZ = 0; scaleZ < scale; scaleZ++) {
                            for (int scaleX = 0; scaleX < scale; scaleX++) {
                                for (int index = blockZ * scale + scaleZ - pcfRadius;
                                     index <= blockZ * scale + scaleZ + pcfRadius;
                                     index++) {
                                    sum += getShadowData2(blockX * scale + scaleX, index);
                                }
                            }
                        }
                        handlingBlock.color = multiplyColor(
                            handlingBlock.color,
                            1.0f - sum / static_cast<float>((2 * pcfRadius + 1) * scale * scale)
                        );
                    }
                }

                northChunkShadowData    = handlingChunkShadowData;
                handlingChunkShadowData = southChunkShadowData;
            }
        }
    } else {
        for (int chunkX = 0; chunkX < 16; chunkX++) {
            for (int chunkZ = 0; chunkZ < 16; chunkZ++) {
                auto handlingChunk = handlingRegion[chunkZ][chunkX];
                if (!handlingChunk) continue;
                for (int blockZ = 0; blockZ < 16; blockZ++) {
                    for (int blockX = 0; blockX < 16; blockX++) {
                        auto& handlingBlock   = handlingChunk->blocksData[blockZ][blockX];
                        float finalShadowData = 0.0f;
                        for (int scaleZ = 0; scaleZ < scale; scaleZ++) {
                            for (int scaleX = 0; scaleX < scale; scaleX++) {
                                finalShadowData += handlingBlock.shadowOriginData[scaleZ][scaleX];
                            }
                        }
                        handlingBlock.color = multiplyColor(
                            handlingBlock.color,
                            1.0f - finalShadowData / static_cast<float>(scale * scale)
                        );
                    }
                }
            }
        }
    }
}

void RegionShadowRenderer::applyBevel(int scale) {
    // 静态缓存：表 + 上次使用的scale
    static std::array<float, 81> cachedTable;
    static int                   cachedScale = -1;

    // 仅在scale变化时重建表
    if (scale != cachedScale) {
        cachedTable = buildBevelTable(scale);
        cachedScale = scale;
    }

    int dimId = handlingRegionPos.dimId;

    int  h      = 0;
    auto getRel = [&h](int neigh) {
        if (neigh > h) return 2;
        if (neigh < h) return 1;
        return 0;
    };

    for (int chunkZ = 0; chunkZ < 16; chunkZ++) {
        auto westChunk = getChunk(ChunkPosWithDim{-1, chunkZ, dimId});
        for (int chunkX = 0; chunkX < 16; chunkX++) {
            auto handlingChunk = handlingRegion[chunkZ][chunkX];
            if (!handlingChunk) {
                westChunk = handlingChunk;
                continue;
            }
            auto eastChunk  = getChunk(ChunkPosWithDim{chunkX + 1, chunkZ, dimId});
            auto northChunk = getChunk(ChunkPosWithDim{chunkX, chunkZ - 1, dimId});
            auto southChunk = getChunk(ChunkPosWithDim{chunkX, chunkZ + 1, dimId});
            for (int blockZ = 0; blockZ < 16; blockZ++) {
                h      = handlingChunk->getBlockBaseData(ChunkWorldPos{0, blockZ}).solidHeight;
                int hw = westChunk ? westChunk->getBlockBaseData(ChunkWorldPos{15, blockZ}).solidHeight : h;
                for (int blockX = 0; blockX < 16; blockX++) {
                    int he = h, hn = h, hs = h;

                    if (blockX != 15)
                        he = handlingChunk->getBlockBaseData(ChunkWorldPos{blockX + 1, blockZ}).solidHeight;
                    else if (eastChunk) he = eastChunk->getBlockBaseData(ChunkWorldPos{0, blockZ}).solidHeight;

                    if (blockZ) hn = handlingChunk->getBlockBaseData(ChunkWorldPos{blockX, blockZ - 1}).solidHeight;
                    else if (northChunk) hn = northChunk->getBlockBaseData(ChunkWorldPos{blockX, 15}).solidHeight;

                    if (blockZ != 15)
                        hs = handlingChunk->getBlockBaseData(ChunkWorldPos{blockX, blockZ + 1}).solidHeight;
                    else if (southChunk) hs = southChunk->getBlockBaseData(ChunkWorldPos{blockX, 0}).solidHeight;

                    int rw = getRel(hw);
                    int re = getRel(he);
                    int rn = getRel(hn);
                    int rs = getRel(hs);

                    int index = rw * 27 + re * 9 + rn * 3 + rs;

                    float avgFactor = cachedTable[index];

                    if (avgFactor != 1.0f) {
                        auto& color = handlingChunk->getBlockData(ChunkWorldPos{blockX, blockZ}).color;
                        color       = multiplyColor(color, avgFactor);
                    }
                    hw = h;
                    h  = he;
                }
            }
            westChunk = handlingChunk;
        }
    }
}

void RegionShadowRenderer::applyStyle2() {
    auto& cfg   = config::getConfig().terrain.shadow;
    int   scale = std::clamp(cfg.renderScale, 1, 16);

    applyShadowMap(scale);
    applyBevel(scale);
}

} // namespace map_demo
