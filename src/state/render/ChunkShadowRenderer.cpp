#include "ChunkShadowRenderer.h"

#include "ShadowRenderUtils.h"
#include "config/Config.h"
#include "data/BlockColor.h"
#include "data/BlockDataBase.h"
#include "data/pos/ChunkPosWithDim.h"
#include "data/pos/ChunkWorldPos.h"
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

void ChunkShadowRenderer::bake(const std::shared_ptr<ChunkCacheData>& data) {
    if (!data || !data->loadChunkBaseData) return;

    // Snapshot raw data under lock, then bake offline without holding the lock
    {
        std::shared_lock<std::shared_mutex> lock(data->mutex_);
        handlingChunk = std::make_shared<ShadowRenderChunkData>(*data);
    }

    auto& cfg = config::getConfig().terrain.shadow;
    if (cfg.transparentWater) applyWaterOverlay();

    if (cfg.renderStyle == 1) {
        applyStyle1();
    } else if (cfg.renderStyle == 2) {
        applyStyle2();
    }

    {
        std::unique_lock<std::shared_mutex> lock(data->mutex_);
        for (int chunkWorldZ = 0; chunkWorldZ < 16; chunkWorldZ++) {
            for (int chunkWorldX = 0; chunkWorldX < 16; chunkWorldX++) {
                auto& blockData            = data->blocksData[chunkWorldZ][chunkWorldX];
                auto& shadowBlockData      = handlingChunk->blocksData[chunkWorldZ][chunkWorldX];
                blockData.bakedColor       = shadowBlockData.color;
                blockData.shadowOriginData = std::move(shadowBlockData.shadowOriginData);
            }
        }
        data->shadowScale = handlingChunk->shadowScale;
    }
}

// Style 1: simple heightmap gradient shadow, light from northwest
void ChunkShadowRenderer::applyStyle1() {
    auto& cfg   = config::getConfig().terrain.shadow;
    int   level = cfg.shadowLevel;
    if (level <= 0) level = 100;

    if (!handlingChunk) return;

    int dimId = handlingChunkPos.dimId;

    auto westChunk  = getChunk(ChunkPosWithDim(-1, 0, dimId));
    auto northChunk = getChunk(ChunkPosWithDim(0, -1, dimId));
    for (int chunkWorldZ = 0; chunkWorldZ < 16; chunkWorldZ++) {
        for (int chunkWorldX = 0; chunkWorldX < 16; chunkWorldX++) {
            auto& blockInfo = handlingChunk->blocksData[chunkWorldZ][chunkWorldX];
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
}

void ChunkShadowRenderer::applyWaterOverlay() {
    // for (int z = 0; z < ShadowRegion::SIZE; ++z) {
    //     for (int x = 0; x < ShadowRegion::SIZE; ++x) {
    //         const auto& info = getInfo(x, z);
    //         if (info.waterDepth == 0) continue;

    //         float opacity = std::min(0.15f * static_cast<float>(info.waterDepth), 0.85f);
    //         setPixel(x, z, blendColors(getPixel(x, z), info.waterSurfaceColor, opacity));
    //     }
    // }
}

void ChunkShadowRenderer::applyShadowMap(int scale) {
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

    int dimId = handlingChunkPos.dimId;

    int maxY = 0;
    if (!dimId) maxY = 320;
    else if (dimId == 1) maxY = 128;
    else if (dimId == 2) maxY = 256;

    if (sunX <= 0 && sunZ <= 0) {
        auto chunk = handlingChunk;
        if (chunk) {
            auto westChunk      = getChunkWithEffectiveShadowData(ChunkPosWithDim{-1, 0, dimId}, scale);
            auto northWestChunk = getChunkWithEffectiveShadowData(ChunkPosWithDim{-1, -1, dimId}, scale);
            auto northChunk     = getChunkWithEffectiveShadowData(ChunkPosWithDim{0, -1, dimId}, scale);
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
                        } else if (westBlock) northWestShadowData = westBlock->shadowOriginData[scaleZ - 1][scale - 1];
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

                            float offsetX = static_cast<float>(blockX)
                                          + (static_cast<float>(scaleX) + 0.5f) / static_cast<float>(scale);
                            float offsetZ = static_cast<float>(blockZ)
                                          + (static_cast<float>(scaleZ) + 0.5f) / static_cast<float>(scale);
                            auto lastOffsetPos = WorldPos{0x7fffffff, 0x7fffffff, dimId};
                            for (int s = 1; s <= kMaxSteps; ++s) {
                                int sx = static_cast<int>(offsetX + static_cast<float>(s) * sdx);
                                int sz = static_cast<int>(offsetZ + static_cast<float>(s) * sdz);
                                if (sx != lastOffsetPos.x || sz != lastOffsetPos.z) {
                                    lastOffsetPos.x   = sx;
                                    lastOffsetPos.z   = sz;
                                    int currentHeight = h + static_cast<int>(static_cast<float>(s) * dzPerStep + 0.01f);
                                    if (getHeight(lastOffsetPos) > currentHeight) {
                                        handlingBlockData.shadowOriginData[scaleZ][scaleX] = kShadowDarkness;
                                        break;
                                    } else if (currentHeight > maxY) break;
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
        }
    } else {
        auto chunk = handlingChunk;
        if (chunk) {
            for (int blockZ = 0; blockZ < 16; blockZ++) {
                for (int blockX = 0; blockX < 16; blockX++) {
                    auto& shadowOriginData = chunk->blocksData[blockZ][blockX].shadowOriginData;
                    shadowOriginData.assign(scale, std::vector<float>(scale, 0.0f));
                    auto& handlingBlockData = chunk->getBlockData(ChunkWorldPos(blockX, blockZ));
                    int   h                 = handlingBlockData.height;
                    for (int scaleZ = 0; scaleZ < scale; scaleZ++) {
                        for (int scaleX = 0; scaleX < scale; scaleX++) {
                            float offsetX = static_cast<float>(blockX)
                                          + (static_cast<float>(scaleX) + 0.5f) / static_cast<float>(scale);
                            float offsetZ = static_cast<float>(blockZ)
                                          + (static_cast<float>(scaleZ) + 0.5f) / static_cast<float>(scale);
                            auto lastOffsetPos = WorldPos{0x7fffffff, 0x7fffffff, dimId};
                            for (int s = 1; s <= kMaxSteps * scale; ++s) {
                                int sx = static_cast<int>(offsetX + static_cast<float>(s) * sdx);
                                int sz = static_cast<int>(offsetZ + static_cast<float>(s) * sdz);
                                if (sx != lastOffsetPos.x || sz != lastOffsetPos.z) {
                                    lastOffsetPos.x   = sx;
                                    lastOffsetPos.z   = sz;
                                    int currentHeight = h + static_cast<int>(static_cast<float>(s) * dzPerStep + 0.01f);
                                    if (getHeight(lastOffsetPos) > currentHeight) {
                                        handlingBlockData.shadowOriginData[scaleZ][scaleX] = kShadowDarkness;
                                        break;
                                    } else if (currentHeight > maxY) break;
                                }
                            }
                        }
                    }
                }
            }
            chunk->shadowScale = scale;
        }
    }

    const int pcfRadius = std::clamp(cfg.pcfRadius, 0, 8);

    if (pcfRadius) {
        std::vector<std::vector<float>> northShadowData;
        std::vector<std::vector<float>> handlingShadowData;
        std::vector<std::vector<float>> southShadowData;

        std::shared_ptr<const ChunkDataBase> westChunk         = nullptr;
        std::shared_ptr<const ChunkDataBase> handlingChunkData = nullptr;
        std::shared_ptr<const ChunkDataBase> eastChunk         = nullptr;

        auto getShadowData =
            [&westChunk, &handlingChunkData, &eastChunk, &scale](int sx, int sz) -> std::optional<float> {
            if (sx < 0) {
                if (!westChunk) return std::nullopt;
                return westChunk->getBlockBaseData(ChunkWorldPos{(sx + 16 * scale) / scale, sz / scale})
                    .shadowOriginData[sz % scale][(sx + 16 * scale) % scale];
            } else if (sx < 16 * scale) {
                if (!handlingChunkData) return std::nullopt;
                return handlingChunkData->getBlockBaseData(ChunkWorldPos{sx / scale, sz / scale})
                    .shadowOriginData[sz % scale][sx % scale];
            } else {
                if (!eastChunk) return std::nullopt;
                return eastChunk->getBlockBaseData(ChunkWorldPos{sx / scale - 16, sz / scale})
                    .shadowOriginData[sz % scale][sx % scale];
            }
        };

        for (int chunkZ = -1; chunkZ <= 1; chunkZ++) {
            westChunk             = getChunkWithEffectiveShadowData(ChunkPosWithDim{-1, chunkZ, dimId}, scale);
            handlingChunkData     = getChunkWithEffectiveShadowData(ChunkPosWithDim{0, chunkZ, dimId}, scale);
            eastChunk             = getChunkWithEffectiveShadowData(ChunkPosWithDim{1, chunkZ, dimId}, scale);
            auto& chunkShadowData = (chunkZ == -1) ? northShadowData
                                  : (chunkZ == 0)  ? handlingShadowData
                                                   : southShadowData;
            int   zSize;
            if (chunkZ == -1 || chunkZ == 1) zSize = pcfRadius;
            else zSize = 16 * scale;
            chunkShadowData.resize(zSize);
            if (!westChunk && !handlingChunkData && !eastChunk) {
                for (int sZ = 0; sZ < zSize; sZ++) {
                    chunkShadowData[sZ].resize(16 * scale, 0.0f);
                    for (int sX = 0; sX < 16 * scale; sX++) {
                        chunkShadowData[sZ][sX] = 0.0f;
                    }
                }
            } else {
                for (int sZ = 0; sZ < zSize; sZ++) {
                    chunkShadowData[sZ].resize(16 * scale, 0.0f);
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
                        if (count) chunkShadowData[sZ][sX] = sum / static_cast<float>(count);
                        else chunkShadowData[sZ][sX] = 0.0f;
                    }
                }
            }
        }

        auto getShadowData2 =
            [&northShadowData, &handlingShadowData, &southShadowData, &scale](int sx, int sz) -> float {
            if (sz < 0) return northShadowData[northShadowData.size() + sz][sx];
            else if (sz < 16 * scale) return handlingShadowData[sz][sx];
            else return southShadowData[sz - 16 * scale][sx];
        };

        if (handlingChunk) {
            for (int blockZ = 0; blockZ < 16; blockZ++) {
                for (int blockX = 0; blockX < 16; blockX++) {
                    auto& handlingBlock = handlingChunk->blocksData[blockZ][blockX];
                    float sum           = 0.0f;
                    for (int scaleZ = 0; scaleZ < scale; scaleZ++) {
                        for (int scaleX = 0; scaleX < scale; scaleX++) {
                            for (int index = 16 * blockZ + scaleZ - pcfRadius;
                                 index <= 16 * blockZ + scaleZ + pcfRadius;
                                 index++) {
                                sum += getShadowData2(16 * blockX + scaleX, index);
                            }
                        }
                    }
                    handlingBlock.color = multiplyColor(
                        handlingBlock.color,
                        1.0f - sum / static_cast<float>((2 * pcfRadius + 1) * scale * scale)
                    );
                }
            }
        }
    } else {
        if (handlingChunk) {
            for (int blockZ = 0; blockZ < 16; blockZ++) {
                for (int blockX = 0; blockX < 16; blockX++) {
                    auto& handlingBlock   = handlingChunk->blocksData[blockZ][blockX];
                    float finalShadowData = 0.0f;
                    for (int scaleZ = 0; scaleZ < scale; scaleZ++) {
                        for (int scaleX = 0; scaleX < scale; scaleX++) {
                            finalShadowData += handlingBlock.shadowOriginData[scaleZ][scaleX];
                        }
                    }
                    handlingBlock.color =
                        multiplyColor(handlingBlock.color, 1.0f - finalShadowData / static_cast<float>(scale * scale));
                }
            }
        }
    }
}

void ChunkShadowRenderer::applyBevel(int scale) {
    // 静态缓存：表 + 上次使用的scale
    static std::array<float, 81> cachedTable;
    static int                   cachedScale = -1;

    // 仅在scale变化时重建表
    if (scale != cachedScale) {
        cachedTable = buildBevelTable(scale);
        cachedScale = scale;
    }

    if (!handlingChunk) return;

    int dimId = handlingChunkPos.dimId;

    int  h      = 0;
    auto getRel = [&h](int neigh) {
        if (neigh > h) return 2;
        if (neigh < h) return 1;
        return 0;
    };

    auto westChunk  = getChunk(ChunkPosWithDim{-1, 0, dimId});
    auto eastChunk  = getChunk(ChunkPosWithDim{1, 0, dimId});
    auto northChunk = getChunk(ChunkPosWithDim{0, -1, dimId});
    auto southChunk = getChunk(ChunkPosWithDim{0, 1, dimId});
    for (int blockZ = 0; blockZ < 16; blockZ++) {
        h      = handlingChunk->getBlockBaseData(ChunkWorldPos{0, blockZ}).solidHeight;
        int hw = westChunk ? westChunk->getBlockBaseData(ChunkWorldPos{15, blockZ}).solidHeight : h;
        for (int blockX = 0; blockX < 16; blockX++) {
            int he = h, hn = h, hs = h;

            if (blockX != 15) he = handlingChunk->getBlockBaseData(ChunkWorldPos{blockX + 1, blockZ}).solidHeight;
            else if (eastChunk) he = eastChunk->getBlockBaseData(ChunkWorldPos{0, blockZ}).solidHeight;

            if (blockZ) hn = handlingChunk->getBlockBaseData(ChunkWorldPos{blockX, blockZ - 1}).solidHeight;
            else if (northChunk) hn = northChunk->getBlockBaseData(ChunkWorldPos{blockX, 15}).solidHeight;

            if (blockZ != 15) hs = handlingChunk->getBlockBaseData(ChunkWorldPos{blockX, blockZ + 1}).solidHeight;
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
}

void ChunkShadowRenderer::applyStyle2() {
    auto& cfg   = config::getConfig().terrain.shadow;
    int   scale = std::clamp(cfg.renderScale, 1, 16);

    applyShadowMap(scale);
    applyBevel(scale);
}

} // namespace map_demo