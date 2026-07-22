#include "RegionShadowRenderer.h"

#include "config/Config.h"
#include "data/BlockColor.h"
#include "data/BlockDataBase.h"
#include "data/cache/MapCacheManager.h"
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

namespace {

inline int clamp255(int v) { return std::clamp(v, 0, 255); }

inline BlockColor multiplyColor(BlockColor c, float factor) {
    return BlockColor{
        static_cast<std::uint8_t>(clamp255(static_cast<int>(static_cast<float>(c.r) * factor))),
        static_cast<std::uint8_t>(clamp255(static_cast<int>(static_cast<float>(c.g) * factor))),
        static_cast<std::uint8_t>(clamp255(static_cast<int>(static_cast<float>(c.b) * factor))),
        c.a
    };
}

// inline BlockColor blendColors(BlockColor base, BlockColor overlay, float overlayFactor) {
//     float baseFactor = 1.0f - overlayFactor;
//     return BlockColor{
//         static_cast<std::uint8_t>(clamp255(
//             static_cast<int>(static_cast<float>(base.r) * baseFactor + static_cast<float>(overlay.r) * overlayFactor)
//         )),
//         static_cast<std::uint8_t>(clamp255(
//             static_cast<int>(static_cast<float>(base.g) * baseFactor + static_cast<float>(overlay.g) * overlayFactor)
//         )),
//         static_cast<std::uint8_t>(clamp255(
//             static_cast<int>(static_cast<float>(base.b) * baseFactor + static_cast<float>(overlay.b) * overlayFactor)
//         )),
//         base.a
//     };
// }

} // namespace

void RegionShadowRenderer::bake(const std::shared_ptr<RegionCacheData>& data) {
    if (!data) return;

    // Snapshot raw data under lock, then bake offline without holding the lock
    if (!data->takeBakedDirty()) return;
    for (int regionChunkZ = 0; regionChunkZ < 16; regionChunkZ++) {
        for (int regionChunkX = 0; regionChunkX < 16; regionChunkX++) {
            auto chunkData = data->getChunkData(RegionChunkPos(regionChunkX, regionChunkZ));
            if (!chunkData || !chunkData->loadChunkBaseData) continue;
            std::shared_lock<std::shared_mutex> lock(chunkData->mutex_);
            handlingRegion[regionChunkZ][regionChunkX] = std::make_shared<ShadowRenderChunkData>(*chunkData);
        }
    }

    auto& cfg = config::getConfig().terrain.shadow;
    if (cfg.transparentWater) applyWaterOverlay();

    if (cfg.renderStyle == 1) {
        applyStyle1();
    } else if (cfg.renderStyle == 2) {
        applyStyle2();
    }

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
        }
    }
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
                    BlockColor c = blockInfo.color;
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

    if (sunX <= 0) {
        if (sunZ <= 0) {
            for (int chunkZ = 0; chunkZ < 16; chunkZ++) {
                auto westChunk = getChunkWithEffectiveShadowData(ChunkPosWithDim{-1, chunkZ, dimId}, scale);
                auto northWestChunk =
                    getChunkWithEffectiveShadowData(ChunkPosWithDim{-1, chunkZ - 1, dimId}, scale);
                for (int chunkX = 0; chunkX < 16; chunkX++) {
                    auto chunk = handlingRegion[chunkZ][chunkX];
                    if (!chunk) {
                        westChunk = chunk;
                        northWestChunk =
                            getChunkWithEffectiveShadowData(ChunkPosWithDim{chunkX, chunkZ - 1, dimId}, scale);
                        continue;
                    }
                    auto northChunk =
                        getChunkWithEffectiveShadowData(ChunkPosWithDim{chunkX, chunkZ - 1, dimId}, scale);
                    for (int blockZ = 0; blockZ < 16; blockZ++) {
                        const BlockDataBase* westBlock = nullptr;
                        if (westChunk) westBlock = &westChunk->getBlockBaseData(ChunkWorldPos{15, blockZ});
                        const BlockDataBase* northWestBlock = nullptr;
                        if (!blockZ) {
                            if (northWestChunk)
                                northWestBlock = &northWestChunk->getBlockBaseData(ChunkWorldPos{15, 15});
                        } else if (westChunk)
                            northWestBlock = &westChunk->getBlockBaseData(ChunkWorldPos{15, blockZ - 1});
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
                                        if (northBlock)
                                            northShadowData = northBlock->shadowOriginData[scale - 1][scaleX];
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
                                        int sx = static_cast<int>(offsetX + static_cast<float>(s) * sdx);
                                        int sz = static_cast<int>(offsetZ + static_cast<float>(s) * sdz);
                                        if (sx != lastOffsetPos.x || sz != lastOffsetPos.z) {
                                            lastOffsetPos.x = sx;
                                            lastOffsetPos.z = sz;
                                            int currentHeight =
                                                h + static_cast<int>(static_cast<float>(s) * dzPerStep + 0.01f);
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
                    westChunk          = chunk;
                    northWestChunk     = northChunk;
                }
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
                                    int sx = static_cast<int>(offsetX + static_cast<float>(s) * sdx);
                                    int sz = static_cast<int>(offsetZ + static_cast<float>(s) * sdz);
                                    if (sx != lastOffsetPos.x || sz != lastOffsetPos.z) {
                                        lastOffsetPos.x = sx;
                                        lastOffsetPos.z = sz;
                                        int currentHeight =
                                            h + static_cast<int>(static_cast<float>(s) * dzPerStep + 0.01f);
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
                auto handlingChunk = handlingRegion[chunkZ][chunkX];
                if (!handlingChunk) continue;
                // for (int sZ = 0; sZ < 16 * scale; sZ++) {
                //     for (int sX = 0; sX < 16 * scale; sX++) {
                //         float sum = 0.0f;
                //         for (int index = sZ - pcfRadius; index <= sZ + pcfRadius; index++)
                //             sum += getShadowData2(sX, index);
                //         handlingChunk->blocksData[sZ / scale][sX / scale].shadowOriginData[sZ % scale][sX % scale] =
                //             sum / static_cast<float>(2 * pcfRadius + 1);
                //     }
                // }
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

std::array<float, 81> buildBevelTable(int scale) {
    constexpr float kEdgeBright  = 1.18f;
    constexpr float kEdgeDark    = 0.72f;
    constexpr float kCornerBoost = 0.40f;

    const int   edgeW       = std::max(1, scale / 6);
    const float rcpEw       = 1.0f / static_cast<float>(edgeW);
    const int   totalPixels = scale * scale;

    std::array<float, 81> table{};

    // 枚举所有关系组合
    for (int hl = 0; hl < 3; ++hl)
        for (int hr = 0; hr < 3; ++hr)
            for (int ht = 0; ht < 3; ++ht)
                for (int hb = 0; hb < 3; ++hb) {
                    float sumFactor = 0.0f;

                    for (int dy = 0; dy < scale; ++dy) {
                        float tyT = (dy < edgeW) ? 1.0f - static_cast<float>(dy) * rcpEw : 0.0f;
                        float tyB = (dy >= scale - edgeW) ? static_cast<float>(dy - (scale - edgeW)) * rcpEw : 0.0f;

                        for (int dx = 0; dx < scale; ++dx) {
                            float txL = (dx < edgeW) ? 1.0f - static_cast<float>(dx) * rcpEw : 0.0f;
                            float txR = (dx >= scale - edgeW) ? static_cast<float>(dx - (scale - edgeW)) * rcpEw : 0.0f;

                            if (txL == 0.0f && txR == 0.0f && tyT == 0.0f && tyB == 0.0f) {
                                sumFactor += 1.0f;
                                continue;
                            }

                            float factor = 1.0f;

                            // 边缘效应
                            auto applyEdge = [&](float t, int rel) {
                                if (t <= 0.0f) return;
                                if (rel == 1) factor *= 1.0f + (kEdgeBright - 1.0f) * t;
                                else if (rel == 2) factor *= 1.0f + (kEdgeDark - 1.0f) * t;
                            };
                            applyEdge(txL, hl);
                            applyEdge(txR, hr);
                            applyEdge(tyT, ht);
                            applyEdge(tyB, hb);

                            // 角落效应
                            auto applyCorner = [&](float tc, int r1, int r2) {
                                if (tc <= 0.0f) return;
                                if (r1 == 1 && r2 == 1) factor *= 1.0f + (kEdgeBright - 1.0f) * tc * kCornerBoost;
                                else if (r1 == 2 && r2 == 2) factor *= 1.0f + (kEdgeDark - 1.0f) * tc * kCornerBoost;
                            };
                            applyCorner(std::min(txL, tyT), hl, ht);
                            applyCorner(std::min(txR, tyT), hr, ht);
                            applyCorner(std::min(txL, tyB), hl, hb);
                            applyCorner(std::min(txR, tyB), hr, hb);

                            factor     = std::clamp(factor, 0.55f, 1.58f);
                            sumFactor += factor;
                        }
                    }

                    int index    = hl * 27 + hr * 9 + ht * 3 + hb;
                    table[index] = sumFactor / static_cast<float>(totalPixels);
                }

    return table;
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

void traceRay(
    std::vector<ChunkPosWithDim>&        out,
    std::unordered_set<ChunkPosWithDim>& visited,
    WorldPos                             pos,
    int                                  originX,
    int                                  originZ,
    float                                dirX,
    float                                dirZ,
    float                                maxDist,
    int                                  higherHeight,
    int                                  lowerHeight,
    float                                tanZenith
) {
    auto& mapCacheManager = MapCacheManager::getInstance();

    auto curX      = static_cast<float>(originX);
    auto curZ      = static_cast<float>(originZ);
    int  curChunkX = static_cast<int>(std::floor(curX / 16.0f));
    int  curChunkZ = static_cast<int>(std::floor(curZ / 16.0f));

    float dist = 0.0f;

    while (dist < maxDist) {
        ChunkPosWithDim chunk{curChunkX, curChunkZ, pos.dimId};

        if (!visited.contains(chunk)) {
            visited.emplace(chunk);

            int chunkMinX = curChunkX * 16;
            int chunkMaxX = curChunkX * 16 + 16;
            int chunkMinZ = curChunkZ * 16;
            int chunkMaxZ = curChunkZ * 16 + 16;

            // 射线起点到该 chunk 的最近点
            int  closestX    = std::clamp(originX, chunkMinX, chunkMaxX);
            int  closestZ    = std::clamp(originZ, chunkMinZ, chunkMaxZ);
            auto minDistance = static_cast<float>(
                std::sqrt((closestX - originX) * (closestX - originX) + (closestZ - originZ) * (closestZ - originZ))
            );

            // 射线起点到该 chunk 的最远角
            int  farX = std::abs(originX - chunkMinX) > std::abs(originX - chunkMaxX) ? chunkMinX : chunkMaxX;
            int  farZ = std::abs(originZ - chunkMinZ) > std::abs(originZ - chunkMaxZ) ? chunkMinZ : chunkMaxZ;
            auto maxDistance =
                static_cast<float>(std::sqrt((farX - originX) * (farX - originX) + (farZ - originZ) * (farZ - originZ))
                );

            auto chunkData = mapCacheManager.getChunk(chunk);
            if (chunkData) {
                // 1. 较高高度在最小距离处都够不着该 chunk 最低点
                //    => 该 chunk 在新旧状态下都不在阴影中
                if (static_cast<float>(higherHeight) - minDistance * tanZenith
                    < static_cast<float>(chunkData->minHeight)) {
                    break;
                }

                // 2. 较低高度在最大距离处仍能覆盖该 chunk 最高点
                //    => 该 chunk 在新旧状态下都被完全阴影覆盖，状态无变化
                if (static_cast<float>(lowerHeight) - maxDistance * tanZenith
                    >= static_cast<float>(chunkData->maxHeight)) {
                    continue;
                }
                out.emplace_back(chunk);
            }
        }

        // 计算下一个 chunk 边界
        int nextX = (dirX >= 0.0f) ? (curChunkX + 1) * 16 : curChunkX * 16;
        int nextZ = (dirZ >= 0.0f) ? (curChunkZ + 1) * 16 : curChunkZ * 16;

        float tX = (dirX != 0.0f) ? (static_cast<float>(nextX) - curX) / dirX : std::numeric_limits<float>::max();
        float tZ = (dirZ != 0.0f) ? (static_cast<float>(nextZ) - curZ) / dirZ : std::numeric_limits<float>::max();

        if (tX <= 1e-5f) tX = std::numeric_limits<float>::max();
        if (tZ <= 1e-5f) tZ = std::numeric_limits<float>::max();

        float stepDist = std::min(tX, tZ);

        if (dist + stepDist > maxDist) break;

        curX += dirX * stepDist;
        curZ += dirZ * stepDist;
        dist += stepDist;

        if (std::abs(stepDist - tX) < 1e-4f) curChunkX += (dirX >= 0.0f) ? 1 : -1;
        if (std::abs(stepDist - tZ) < 1e-4f) curChunkZ += (dirZ >= 0.0f) ? 1 : -1;
    }
}

std::vector<ChunkPosWithDim>
getAffectedChunk(int oriHeight, int height, WorldPos pos, float azimuth_rad, float zenith_rad) {
    int higherHeight = std::max(oriHeight, height);
    int lowerHeight  = std::min(oriHeight, height);

    float tanZenith = std::tan(zenith_rad);

    std::vector<ChunkPosWithDim>        res;
    std::unordered_set<ChunkPosWithDim> visited;
    res.reserve(7);
    visited.reserve(10);

    auto originChunk = ChunkPosWithDim{pos};
    res.emplace_back(originChunk);
    visited.emplace(originChunk);

    // 下游方向
    float dirX = -std::sin(azimuth_rad);
    float dirZ = std::cos(azimuth_rad);
    if (std::abs(dirX) < 1e-5f) dirX = 0.0f;
    if (std::abs(dirZ) < 1e-5f) dirZ = 0.0f;

    int corner1X = pos.x + (dirX > 0.0f ? 1 : 0);
    int corner1Z = pos.z + (dirZ < 0.0f ? 1 : 0);
    int corner2X = pos.x + (dirX < 0.0f ? 1 : 0);
    int corner2Z = pos.z + (dirZ > 0.0f ? 1 : 0);

    float maxDist = 96.0f;

    // traceRay(res, visited, pos, centerX, centerZ, dirX, dirZ, maxDist, higherHeight, lowerHeight, tanZenith);
    traceRay(res, visited, pos, corner1X, corner1Z, dirX, dirZ, maxDist, higherHeight, lowerHeight, tanZenith);
    traceRay(res, visited, pos, corner2X, corner2Z, dirX, dirZ, maxDist, higherHeight, lowerHeight, tanZenith);

    auto farChunk = ChunkPosWithDim{
        WorldPos{
                 static_cast<int>(static_cast<float>(corner1X) + maxDist * dirX),
                 static_cast<int>(static_cast<float>(corner2Z) + maxDist * dirZ),
                 pos.dimId
        }
    };
    if (!visited.contains(farChunk)) {

        int chunkMinX = farChunk.x * 16;
        int chunkMaxX = farChunk.x * 16 + 16;
        int chunkMinZ = farChunk.z * 16;
        int chunkMaxZ = farChunk.z * 16 + 16;

        // 射线起点到该 chunk 的最近点
        int  closestX    = std::clamp(farChunk.x, chunkMinX, chunkMaxX);
        int  closestZ    = std::clamp(farChunk.z, chunkMinZ, chunkMaxZ);
        auto minDistance = static_cast<float>(std::sqrt(
            (closestX - farChunk.x) * (closestX - farChunk.x) + (closestZ - farChunk.z) * (closestZ - farChunk.z)
        ));

        // 射线起点到该 chunk 的最远角
        int  farX        = std::abs(farChunk.x - chunkMinX) > std::abs(farChunk.x - chunkMaxX) ? chunkMinX : chunkMaxX;
        int  farZ        = std::abs(farChunk.z - chunkMinZ) > std::abs(farChunk.z - chunkMaxZ) ? chunkMinZ : chunkMaxZ;
        auto maxDistance = static_cast<float>(
            std::sqrt((farX - farChunk.x) * (farX - farChunk.x) + (farZ - farChunk.z) * (farZ - farChunk.z))
        );

        auto chunkData = MapCacheManager::getInstance().getChunk(farChunk);
        if (chunkData
            && static_cast<float>(higherHeight) - minDistance * tanZenith > static_cast<float>(chunkData->minHeight)
            && static_cast<float>(lowerHeight) - maxDistance * tanZenith < static_cast<float>(chunkData->maxHeight)) {
            res.emplace_back(farChunk);
        }
    }

    return res;
}

} // namespace map_demo
