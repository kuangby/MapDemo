#include "RegionRenderer.h"

#include "config/Config.h"
#include "data/BlockColor.h"
#include "data/BlockDataBase.h"
#include "data/pos/ChunkPosWithDim.h"
#include "data/pos/ChunkWorldPos.h"
#include "data/pos/RegionChunkPos.h"
#include "data/pos/WorldPos.h"
#include "data/shadowRender/ShadowRenderData.h"
#include "mod/MapDemo.h"


#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <memory>
#include <optional>
#include <shared_mutex>
#include <vector>

namespace map_demo {

using Clock = std::chrono::high_resolution_clock;

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

inline BlockColor blendColors(BlockColor base, BlockColor overlay, float overlayFactor) {
    float baseFactor = 1.0f - overlayFactor;
    return BlockColor{
        static_cast<std::uint8_t>(clamp255(
            static_cast<int>(static_cast<float>(base.r) * baseFactor + static_cast<float>(overlay.r) * overlayFactor)
        )),
        static_cast<std::uint8_t>(clamp255(
            static_cast<int>(static_cast<float>(base.g) * baseFactor + static_cast<float>(overlay.g) * overlayFactor)
        )),
        static_cast<std::uint8_t>(clamp255(
            static_cast<int>(static_cast<float>(base.b) * baseFactor + static_cast<float>(overlay.b) * overlayFactor)
        )),
        base.a
    };
}

} // namespace

RegionRenderer& RegionRenderer::getInstance() {
    static RegionRenderer instance;
    return instance;
}

RegionRenderer::RegionRenderer() : worker_([this] { workerLoop(); }) {}

RegionRenderer::~RegionRenderer() {
    // During DLL unload the runtime may already be tearing down.
    // Avoid any logger access or object recreation here.
    safeStopWorker();
}

void RegionRenderer::safeStopWorker() {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        stop_ = true;
    }
    cv_.notify_all();

    if (worker_.joinable()) {
        try {
            worker_.join();
        } catch (...) {
            // If join throws (e.g. runtime already finalized during DLL unload),
            // detach to avoid std::terminate from ~thread().
            try {
                worker_.detach();
            } catch (...) {}
        }
    }
}

void RegionRenderer::shutdown() { safeStopWorker(); }

void RegionRenderer::clearQueueAndWait() {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        stop_ = true;
        while (!queue_.empty()) {
            queue_.pop();
        }
        pending_.clear();
    }
    cv_.notify_all();

    if (worker_.joinable()) {
        try {
            worker_.join();
        } catch (...) {
            try {
                worker_.detach();
            } catch (...) {}
        }
    }

    // restart worker for continued use after world switch
    {
        std::lock_guard<std::mutex> lock(mutex_);
        stop_ = false;
    }
    worker_ = std::thread([this] { workerLoop(); });
}

void RegionRenderer::requestBake(const std::shared_ptr<RegionCacheData>& data, const RegionPos& pos, int dim) {
    if (!data) return;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!data->isBakedDirty()) return;
        if (pending_.count(pos)) return; // already queued
        pending_.insert(pos);
        queue_.push(BakeTask{data, dim, pos});
    }
    cv_.notify_one();
}

void RegionRenderer::workerLoop() {
    while (true) {
        BakeTask task;
        {
            std::unique_lock<std::mutex> lock(mutex_);
            cv_.wait(lock, [this] { return stop_ || !queue_.empty(); });
            if (stop_ && queue_.empty()) return;
            task = queue_.front();
            queue_.pop();
        }

        auto data = task.data.lock();
        if (!data) continue;

        baking_.store(true, std::memory_order_release);
        auto t0 = Clock::now();
        snapshotAndBake(data, task.pos, task.dim);
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - t0).count();
        baking_.store(false, std::memory_order_release);

        {
            std::lock_guard<std::mutex> lock(mutex_);
            pending_.erase(task.pos);
        }

        static int s_workerLog = 0;
        if ((++s_workerLog % 10) == 0 || us > 50000) {
            MapDemo::getInstance().getSelf().getLogger().debug(
                "RegionRenderer::worker bake region=({},{}), dim={}, time={}us",
                task.pos.x,
                task.pos.z,
                task.dim,
                us
            );
        }
    }
}

void RegionRenderer::snapshotAndBake(const std::shared_ptr<RegionCacheData>& data, const RegionPos& pos, int /*dim*/) {
    if (!data) return;

    // Snapshot raw data under lock, then bake offline without holding the lock
    ShadowRenderData shadow(pos);
    if (!data->isBakedDirty()) return;
    for (int regionChunkZ = 0; regionChunkZ < 16; regionChunkZ++) {
        for (int regionChunkX = 0; regionChunkX < 16; regionChunkX++) {
            auto chunkData = data->getChunkData(RegionChunkPos(regionChunkX, regionChunkZ));
            if (!chunkData) return;
            std::shared_lock<std::shared_mutex> lock(chunkData->mutex_);
            shadow.handlingRegion[regionChunkZ][regionChunkX] = std::make_shared<ShadowRenderChunkData>(chunkData);
        }
    }

    auto& cfg = config::getConfig().terrain.shadow;
    if (cfg.transparentWater) applyWaterOverlay(shadow);

    if (cfg.renderStyle == 1) {
        applyStyle1(shadow);
    } else if (cfg.renderStyle == 2) {
        applyStyle2(shadow);
    }

    for (int regionChunkZ = 0; regionChunkZ < 16; regionChunkZ++) {
        for (int regionChunkX = 0; regionChunkX < 16; regionChunkX++) {
            auto chunkData = data->getChunkData(RegionChunkPos(regionChunkX, regionChunkZ));
            if (!chunkData) continue;
            auto                                shadowChunkData = shadow.handlingRegion[regionChunkZ][regionChunkX];
            std::shared_lock<std::shared_mutex> lock(chunkData->mutex_);
            for (int chunkWorldZ = 0; chunkWorldZ < 16; chunkWorldZ++) {
                for (int chunkWorldX = 0; chunkWorldX < 16; chunkWorldX++) {
                    chunkData->blocksData[chunkWorldZ][chunkWorldX].bakedColor =
                        shadowChunkData->blocksData[chunkWorldZ][chunkWorldX].color;
                }
            }
        }
    }
}

// void RegionRenderer::copyRegionToShadow(const RegionCacheData* data, ShadowRegion& shadow, int /*dim*/) {
//     for (int z = 0; z < ShadowRegion::SIZE; ++z) {
//         for (int x = 0; x < ShadowRegion::SIZE; ++x) {
//             shadow.setPixel(x, z, data->getPixel(x, z));

//             BlockRenderInfo bri{};
//             bri.height      = data->getHeight(x, z);
//             bri.solidHeight = data->getSolidHeight(x, z);
//             bri.waterDepth  = data->getWaterDepth(x, z);
//             bri.hasData     = (bri.height > -128);

//             if (bri.waterDepth > 0) {
//                 bri.waterSurfaceColor = BlockColor{64, 94, 241, 255};
//             }

//             shadow.setInfo(x, z, bri);
//         }
//     }
// }

// void RegionRenderer::bake(const RegionData* data, BlockColor* output, int dim) {
//     if (!data || !output) return;
//     auto t0 = Clock::now();

//     ShadowRegion shadow;
//     copyRegionToShadow(data, shadow, dim);

//     auto& cfg = config::getConfig().terrain.shadow;
//     if (cfg.renderStyle == 1) {
//         if (cfg.transparentWater) applyWaterOverlay(shadow);
//         applyStyle1(shadow);
//     } else if (cfg.renderStyle == 2) {
//         applyStyle2(shadow);
//     } else {
//         if (cfg.transparentWater) applyWaterOverlay(shadow);
//     }

//     for (int z = 0; z < ShadowRegion::SIZE; ++z) {
//         for (int x = 0; x < ShadowRegion::SIZE; ++x) {
//             output[z * ShadowRegion::SIZE + x] = shadow.getPixel(x, z);
//         }
//     }

//     auto totalUs = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - t0).count();
//     if (totalUs > 30000) {
//         MapDemo::getInstance().getSelf().getLogger().debug(
//             "RegionRenderer::bake sync slow style={}, time={}us",
//             cfg.renderStyle,
//             totalUs
//         );
//     }
// }

// Style 1: simple heightmap gradient shadow, light from northwest
void RegionRenderer::applyStyle1(ShadowRenderData& shadow) {
    auto& cfg   = config::getConfig().terrain.shadow;
    int   level = cfg.shadowLevel;
    if (level <= 0) level = 100;

    // for (int z = 0; z < ShadowRegion::SIZE; ++z) {
    //     for (int x = 0; x < ShadowRegion::SIZE; ++x) {
    //         if (!shadow.hasData(x, z)) continue;

    //         int16_t cur = shadow.getHeight(x, z);
    //         int16_t sum = cur * 2;
    //         if (x == 0 && z != 0) {
    //             sum = shadow.getHeight(x, z - 1) * 2;
    //         } else if (x != 0 && z == 0) {
    //             sum = shadow.getHeight(x - 1, z) * 2;
    //         } else if (x != 0 && z != 0) {
    //             sum = shadow.getHeight(x, z - 1) + shadow.getHeight(x - 1, z);
    //         }

    //         BlockColor c = shadow.getPixel(x, z);
    //         if (cur * 2 > sum) {
    //             c = BlockColor{
    //                 static_cast<std::uint8_t>(clamp255(c.r * level / 100)),
    //                 static_cast<std::uint8_t>(clamp255(c.g * level / 100)),
    //                 static_cast<std::uint8_t>(clamp255(c.b * level / 100)),
    //                 c.a
    //             };
    //         } else if (cur * 2 < sum) {
    //             c = BlockColor{
    //                 static_cast<std::uint8_t>(clamp255(c.r * 100 / level)),
    //                 static_cast<std::uint8_t>(clamp255(c.g * 100 / level)),
    //                 static_cast<std::uint8_t>(clamp255(c.b * 100 / level)),
    //                 c.a
    //             };
    //     }
    // }
    for (int regionChunkZ = 0; regionChunkZ < 16; regionChunkZ++) {
        auto westChunk = shadow.getChunk(ChunkPosWithDim(-1, regionChunkZ));
        for (int regionChunkX = 0; regionChunkX < 16; regionChunkX++) {
            // if (!shadow.hasData(x, z)) continue;
            auto shadowChunkData = shadow.handlingRegion[regionChunkZ][regionChunkX];
            if (!shadowChunkData) {
                westChunk = shadowChunkData;
                continue;
            }
            auto northChunk = shadow.getChunk(ChunkPosWithDim(regionChunkX, regionChunkZ - 1));
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

void RegionRenderer::applyWaterOverlay(ShadowRenderData& shadow) {
    // for (int z = 0; z < ShadowRegion::SIZE; ++z) {
    //     for (int x = 0; x < ShadowRegion::SIZE; ++x) {
    //         const auto& info = shadow.getInfo(x, z);
    //         if (info.waterDepth == 0) continue;

    //         float opacity = std::min(0.15f * static_cast<float>(info.waterDepth), 0.85f);
    //         shadow.setPixel(x, z, blendColors(shadow.getPixel(x, z), info.waterSurfaceColor, opacity));
    //     }
    // }
}

void RegionRenderer::upscale(
    const ShadowRenderData&                                                                               src,
    std::array<std::array<std::array<std::array<std::vector<std::vector<BlockColor>>, 16>, 16>, 16>, 16>& dst,
    int                                                                                                   scale
) {
    // dst.resize(dstSize * dstSize);
    // for (int z = 0; z < dstSize; ++z) {
    //     int sz = std::min(z / scale, ShadowRegion::SIZE - 1);
    //     for (int x = 0; x < dstSize; ++x) {
    //         int sx               = std::min(x / scale, ShadowRegion::SIZE - 1);
    //         dst[z * dstSize + x] = src.getPixel(sx, sz);
    //     }
    // }
    for (int chunkZ = 0; chunkZ < 16; chunkZ++) {
        for (int chunkX = 0; chunkX < 16; chunkX++) {
            auto  srcChunk = src.handlingRegion[chunkZ][chunkX];
            auto& dstChunk = dst[chunkZ][chunkX];
            for (int z = 0; z < 16; z++) {
                for (int x = 0; x < 16; x++) {
                    auto& srcBlockColor = srcChunk->blocksData[z][x].color;
                    auto& dstBlock      = dstChunk[z][x];
                    dstBlock.reserve(scale);
                    for (int scaleZ = 0; scaleZ < scale; scaleZ++) {
                        dstBlock[scaleZ].reserve(scale);
                        for (int scaleX = 0; scaleX < 16; scaleX++) {
                            dstBlock[scaleZ][scaleX] = srcBlockColor;
                        }
                    }
                }
            }
        }
    }
}

void RegionRenderer::downsample(
    const std::array<std::array<std::array<std::array<std::vector<std::vector<BlockColor>>, 16>, 16>, 16>, 16>& src,
    ShadowRenderData&                                                                                           dst,
    int                                                                                                         scale
) {
    // for (int z = 0; z < ShadowRegion::SIZE; ++z) {
    //     for (int x = 0; x < ShadowRegion::SIZE; ++x) {
    //         int r = 0, g = 0, b = 0, a = 0;
    //         for (int dy = 0; dy < scale; ++dy) {
    //             int sy = z * scale + dy;
    //             if (sy >= srcSize) continue;
    //             for (int dx = 0; dx < scale; ++dx) {
    //                 int sx = x * scale + dx;
    //                 if (sx >= srcSize) continue;
    //                 auto c  = src[sy * srcSize + sx];
    //                 r      += c.r;
    //                 g      += c.g;
    //                 b      += c.b;
    //                 a      += c.a;
    //             }
    //         }
    //         int samples = scale * scale;
    //         dst.setPixel(
    //             x,
    //             z,
    //             BlockColor{
    //                 static_cast<std::uint8_t>(r / samples),
    //                 static_cast<std::uint8_t>(g / samples),
    //                 static_cast<std::uint8_t>(b / samples),
    //                 static_cast<std::uint8_t>(a / samples)
    //             }
    //         );
    //     }
    // }
    int samples = scale * scale;
    for (int chunkZ = 0; chunkZ < 16; chunkZ++) {
        for (int chunkX = 0; chunkX < 16; chunkX++) {
            auto  srcChunk = src[chunkZ][chunkX];
            auto& dstChunk = dst.handlingRegion[chunkZ][chunkX];
            for (int z = 0; z < 16; z++) {
                for (int x = 0; x < 16; x++) {
                    auto& srcBlockColors = srcChunk[z][x];
                    int   r = 0, g = 0, b = 0, a = 0;
                    for (int scaleZ = 0; scaleZ < scale; scaleZ++) {
                        for (int scaleX = 0; scaleX < 16; scaleX++) {
                            auto& subBlockColor  = srcBlockColors[scaleZ][scaleX];
                            r                   += subBlockColor.r;
                            g                   += subBlockColor.g;
                            b                   += subBlockColor.b;
                            a                   += subBlockColor.a;
                        }
                    }
                    dstChunk->blocksData[chunkZ][chunkX].color =
                        BlockColor(r / samples, g / samples, b / samples, a / samples);
                }
            }
        }
    }
}

void RegionRenderer::applyShadowMap(ShadowRenderData& shadow, int scale) {
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
    const float dzPerStep = (sunY / sun2dLen) / static_cast<float>(scale);

    const int HR = 256 * scale;

    // auto coarseH = [&](int hi, int hj, const ShadowRenderData& s) -> float {
    //     int bi = std::clamp(hi / scale, 0, 255);
    //     int bj = std::clamp(hj / scale, 0, 255);
    //     return s.getHeight(bi, bj);
    // };


    // std::array<std::array<std::array<std::array<std::vector<std::vector<float>>, 16>, 16>, 16>, 16> shadowMap;
    // std::vector<float> shadowMap(HR * HR, 1.0f);
    // for (int hj = 0; hj < HR; ++hj) {
    //     for (int hi = 0; hi < HR; ++hi) {
    //         float h = coarseH(hi, hj, shadow);
    //         if (h <= -128) continue;

    //         float fx = static_cast<float>(hi) + 0.5f;
    //         float fy = static_cast<float>(hj) + 0.5f;
    //         for (int s = 1; s <= kMaxSteps; ++s) {
    //             int si = static_cast<int>(fx + s * sdx);
    //             int sj = static_cast<int>(fy + s * sdz);
    //             if (si < 0 || si >= HR || sj < 0 || sj >= HR) break;
    //             float nh = coarseH(si, sj, shadow);
    //             if (nh <= -128) break;
    //             if (nh > h + s * dzPerStep + 0.1f) {
    //                 shadowMap[hj * HR + hi] = kShadowDarkness;
    //                 break;
    //             }
    //         }
    //     }
    // }
    if (sunX <= 0) {
        if (sunZ <= 0) {
            for (int chunkZ = 0; chunkZ < 16; chunkZ++) {
                auto westChunk      = shadow.getChunk(ChunkPosWithDim{-1, chunkZ});
                auto northWestChunk = shadow.getChunk(ChunkPosWithDim{-1, chunkZ - 1});
                for (int chunkX = 0; chunkX < 16; chunkX++) {
                    auto chunk      = shadow.handlingRegion[chunkZ][chunkX];
                    auto northChunk = shadow.getChunk(ChunkPosWithDim(chunkX, chunkZ - 1));
                    for (int blockZ = 0; blockZ < 16; blockZ++) {
                        auto                 westBlock = &westChunk->getBlockBaseData(ChunkWorldPos{15, blockZ});
                        const BlockDataBase* northWestBlock;
                        if (!blockZ) northWestBlock = &northWestChunk->getBlockBaseData(ChunkWorldPos{15, 15});
                        else northWestBlock = &westChunk->getBlockBaseData(ChunkWorldPos{15, blockZ - 1});
                        for (int blockX = 0; blockX < 16; blockX++) {
                            auto& shadowOriginData = chunk->blocksData[blockZ][blockX].shadowOriginData;
                            shadowOriginData.reserve(scale);
                            auto& handlingBlockData =
                                shadow.handlingRegion[chunkZ][chunkX]->getBlockData(ChunkWorldPos(blockX, blockZ));
                            const BlockDataBase* northBlock;
                            if (!blockZ) northBlock = &northChunk->getBlockBaseData(ChunkWorldPos{blockX, 15});
                            else northBlock = &chunk->getBlockBaseData(ChunkWorldPos{blockX, blockZ - 1});
                            bool canSkip = handlingBlockData.height >= westBlock->height
                                        && handlingBlockData.height >= northBlock->height
                                        && handlingBlockData.height >= northWestBlock->height;

                            int h = handlingBlockData.height;
                            for (int scaleZ = 0; scaleZ < scale; scaleZ++) {
                                auto  westShadowData = westBlock->shadowOriginData[scaleZ][scale - 1];
                                float northWestShadowData;
                                if (!scaleZ)
                                    northWestShadowData = northWestBlock->shadowOriginData[scale - 1][scale - 1];
                                else northWestShadowData = westBlock->shadowOriginData[scaleZ - 1][scale - 1];
                                shadowOriginData[scaleZ].reserve(scale);
                                for (int scaleX = 0; scaleX < 16; scaleX++) {
                                    // auto currentShadowData = handlingBlockData.shadowOriginData[scaleZ][scaleX];
                                    float northShadowData;
                                    if (!scaleZ) northShadowData = northBlock->shadowOriginData[scale - 1][scaleX];
                                    else northShadowData = handlingBlockData.shadowOriginData[scaleZ - 1][scaleX];
                                    if (canSkip && westShadowData < 0.0001f && northShadowData < 0.0001f
                                        && northWestShadowData < 0.0001f) {
                                        handlingBlockData.shadowOriginData[scaleZ][scaleX] = 0.0f;
                                        continue;
                                    }

                                    float offsetX = static_cast<float>(chunkX * 16 + blockX)
                                                  + (static_cast<float>(scaleX) + 0.5f) / static_cast<float>(scale);
                                    float offsetZ = static_cast<float>(chunkZ * 16 + blockZ)
                                                  + (static_cast<float>(scaleZ) + 0.5f) / static_cast<float>(scale);
                                    auto lastOffsetPos =
                                        WorldPos{0x7fffffff, 0x7fffffff, shadow.handlingRegionPos.dimId};
                                    for (int s = 1; s <= kMaxSteps * scale; ++s) {
                                        int sx = static_cast<int>(offsetX + static_cast<float>(s) * sdx);
                                        int sz = static_cast<int>(offsetZ + static_cast<float>(s) * sdz);
                                        if (sx != lastOffsetPos.x || sz != lastOffsetPos.z) {
                                            lastOffsetPos.x           = sx;
                                            lastOffsetPos.z           = sz;
                                            auto currentBlockBaseData = shadow.getBlockBaseData(lastOffsetPos);
                                            if (currentBlockBaseData
                                                && currentBlockBaseData->height
                                                       > h
                                                             + static_cast<int>(
                                                                 static_cast<float>(s) * dzPerStep + 0.01f
                                                             )) {
                                                handlingBlockData.shadowOriginData[scaleZ][scaleX] = kShadowDarkness;
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
                    westChunk      = chunk;
                    northWestChunk = northChunk;
                }
            }
        }
    } else {
        for (int chunkZ = 0; chunkZ < 16; chunkZ++) {
            for (int chunkX = 0; chunkX < 16; chunkX++) {
                auto chunk = shadow.handlingRegion[chunkZ][chunkX];
                for (int blockZ = 0; blockZ < 16; blockZ++) {
                    for (int blockX = 0; blockX < 16; blockX++) {
                        auto& shadowOriginData = chunk->blocksData[blockZ][blockX].shadowOriginData;
                        shadowOriginData.reserve(scale);
                        auto& handlingBlockData =
                            shadow.handlingRegion[chunkZ][chunkX]->getBlockData(ChunkWorldPos(blockX, blockZ));
                        int h = handlingBlockData.height;
                        for (int scaleZ = 0; scaleZ < scale; scaleZ++) {
                            shadowOriginData[scaleZ].reserve(scale);
                            for (int scaleX = 0; scaleX < 16; scaleX++) {
                                float offsetX = static_cast<float>(chunkX * 16 + blockX)
                                              + (static_cast<float>(scaleX) + 0.5f) / static_cast<float>(scale);
                                float offsetZ = static_cast<float>(chunkZ * 16 + blockZ)
                                              + (static_cast<float>(scaleZ) + 0.5f) / static_cast<float>(scale);
                                auto lastOffsetPos = WorldPos{0x7fffffff, 0x7fffffff, shadow.handlingRegionPos.dimId};
                                for (int s = 1; s <= kMaxSteps * scale; ++s) {
                                    int sx = static_cast<int>(offsetX + static_cast<float>(s) * sdx);
                                    int sz = static_cast<int>(offsetZ + static_cast<float>(s) * sdz);
                                    if (sx != lastOffsetPos.x || sz != lastOffsetPos.z) {
                                        lastOffsetPos.x           = sx;
                                        lastOffsetPos.z           = sz;
                                        auto currentBlockBaseData = shadow.getBlockBaseData(lastOffsetPos);
                                        if (currentBlockBaseData
                                            && currentBlockBaseData->height
                                                   > h + static_cast<int>(static_cast<float>(s) * dzPerStep + 0.01f)) {
                                            handlingBlockData.shadowOriginData[scaleZ][scaleX] = kShadowDarkness;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    std::array<std::array<std::array<std::array<std::vector<std::vector<BlockColor>>, 16>, 16>, 16>, 16> hrImage;
    // std::vector<BlockColor> hrImage;
    // upscale(shadow, hrImage, scale);

    const int pcfRadius = std::clamp(cfg.pcfRadius, 0, 8);

    // for (int hj = 0; hj < HR; ++hj) {
    //     for (int hi = 0; hi < HR; ++hi) {
    //         if (coarseH(hi, hj, shadow) <= -128) continue;

    //         int i0 = std::max(0, hi - pcfRadius);
    //         int i1 = std::min(HR - 1, hi + pcfRadius);
    //         int j0 = std::max(0, hj - pcfRadius);
    //         int j1 = std::min(HR - 1, hj + pcfRadius);

    //         float sum   = 0.0f;
    //         int   count = 0;
    //         for (int sj = j0; sj <= j1; ++sj) {
    //             for (int si = i0; si <= i1; ++si) {
    //                 if (coarseH(si, sj, shadow) <= -128) continue;
    //                 sum += shadowMap[sj * HR + si];
    //                 ++count;
    //             }
    //         }
    //         if (count == 0) continue;
    //         float shadowFactor = sum / count;
    //         if (shadowFactor >= 1.0f) continue;

    //         hrImage[hj * HR + hi] = multiplyColor(hrImage[hj * HR + hi], shadowFactor);
    //     }
    // }


    // downsample(hrImage, shadow, scale);
    // auto coarseH = [&](int hi, int hj, const ShadowRenderData& s) -> float {
    //     int bi = std::clamp(hi / scale, 0, 255);
    //     int bj = std::clamp(hj / scale, 0, 255);
    //     return s.getHeight(bi, bj);
    // };

    if (pcfRadius) {
        std::array<std::vector<std::vector<float>>, 16> northShadowData;
        std::array<std::vector<std::vector<float>>, 16> southShadowData;
        auto westChunk                                 = shadow.getHelperChunkWithShadowData(ChunkPosWithDim{-1, -1});
        auto handlingChunk                             = shadow.getHelperChunkWithShadowData(ChunkPosWithDim{0, -1});
        std::shared_ptr<const ChunkDataBase> eastChunk = nullptr;

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
                return eastChunk->getBlockBaseData(ChunkWorldPos{sx / scale, sz / scale})
                    .shadowOriginData[sz % scale][sx % scale];
            }
        };

        if (!westChunk && !handlingChunk && !eastChunk) {
            for (int chunkX = 0; chunkX < 16; chunkX++) {
                auto& handlingChunkShadowData = northShadowData[chunkX];
                handlingChunkShadowData.reserve(pcfRadius);
                for (int i = 0; i < pcfRadius; i++) handlingChunkShadowData[i].reserve(16 * scale);
                for (int sZ = 16 * scale - pcfRadius; sZ < 16 * scale; sZ++) {
                    for (int sX = 0; sX < 16 * scale; sX++) {
                        handlingChunkShadowData[sZ - 16 * scale + pcfRadius][sX] = 0.0f;
                    }
                }
            }
        } else {
            for (int chunkX = 0; chunkX < 16; chunkX++) {
                eastChunk                     = shadow.getHelperChunkWithShadowData(ChunkPosWithDim{chunkX + 1, -1});
                auto& handlingChunkShadowData = northShadowData[chunkX];
                handlingChunkShadowData.reserve(pcfRadius);
                for (int i = 0; i < pcfRadius; i++) handlingChunkShadowData[i].reserve(16 * scale);
                for (int sZ = 16 * scale - pcfRadius; sZ < 16 * scale; sZ++) {
                    for (int sX = 0; sX < 16 * scale; sX++) {
                        float sum   = 0.0f;
                        int   count = 0;
                        for (int index = sX - pcfRadius; index <= sX + pcfRadius; index++) {
                            auto shadowData = getShadowData(index, sZ);
                            if (shadowData) {
                                sum += shadowData.value();
                                count++;
                            }
                        }
                        handlingChunkShadowData[sZ - 16 * scale + pcfRadius][sX] = sum / static_cast<float>(count);
                    }
                }
                westChunk     = handlingChunk;
                handlingChunk = eastChunk;
            }
        }
    }
}

void RegionRenderer::applyBevel(ShadowRegion& shadow, int scale) {
    constexpr float kEdgeBright  = 1.18f;
    constexpr float kEdgeDark    = 0.72f;
    constexpr float kCornerBoost = 0.40f;

    const int   edgeW = std::max(1, scale / 6);
    const float rcpEw = 1.0f / static_cast<float>(edgeW);

    const int               HR = ShadowRegion::SIZE * scale;
    std::vector<BlockColor> hrImage;
    upscale(shadow, hrImage, scale, HR);

    for (int bz = 0; bz < ShadowRegion::SIZE; ++bz) {
        for (int bx = 0; bx < ShadowRegion::SIZE; ++bx) {
            float h = shadow.getSolidHeight(bx, bz);
            if (h <= -128) continue;

            float hl  = (bx > 0) ? shadow.getSolidHeight(bx - 1, bz) : h;
            float hr_ = (bx < ShadowRegion::SIZE - 1) ? shadow.getSolidHeight(bx + 1, bz) : h;
            float ht  = (bz > 0) ? shadow.getSolidHeight(bx, bz - 1) : h;
            float hb  = (bz < ShadowRegion::SIZE - 1) ? shadow.getSolidHeight(bx, bz + 1) : h;

            int x0 = bx * scale;
            int y0 = bz * scale;

            for (int dy = 0; dy < scale; ++dy) {
                int   py  = dy;
                float tyT = (py < edgeW) ? 1.0f - py * rcpEw : 0.0f;
                float tyB = (py >= scale - edgeW) ? (py - (scale - edgeW)) * rcpEw : 0.0f;
                for (int dx = 0; dx < scale; ++dx) {
                    int   px  = dx;
                    float txL = (px < edgeW) ? 1.0f - px * rcpEw : 0.0f;
                    float txR = (px >= scale - edgeW) ? (px - (scale - edgeW)) * rcpEw : 0.0f;

                    if (txL == 0.0f && txR == 0.0f && tyT == 0.0f && tyB == 0.0f) continue;

                    float factor    = 1.0f;
                    auto  applyEdge = [&](float t, float cur, float neigh) {
                        if (t <= 0.0f) return;
                        if (cur > neigh) factor *= 1.0f + (kEdgeBright - 1.0f) * t;
                        else if (cur < neigh) factor *= 1.0f + (kEdgeDark - 1.0f) * t;
                    };
                    applyEdge(txL, h, hl);
                    applyEdge(txR, h, hr_);
                    applyEdge(tyT, h, ht);
                    applyEdge(tyB, h, hb);

                    auto applyCorner = [&](float tc, float n1, float n2) {
                        if (tc <= 0.0f) return;
                        if (h > n1 && h > n2) factor *= 1.0f + (kEdgeBright - 1.0f) * tc * kCornerBoost;
                        else if (h < n1 && h < n2) factor *= 1.0f + (kEdgeDark - 1.0f) * tc * kCornerBoost;
                    };
                    applyCorner(std::min(txL, tyT), hl, ht);
                    applyCorner(std::min(txR, tyT), hr_, ht);
                    applyCorner(std::min(txL, tyB), hl, hb);
                    applyCorner(std::min(txR, tyB), hr_, hb);

                    if (factor == 1.0f) continue;
                    factor = std::clamp(factor, 0.55f, 1.58f);

                    int hi                = x0 + dx;
                    int hj                = y0 + dy;
                    hrImage[hj * HR + hi] = multiplyColor(hrImage[hj * HR + hi], factor);
                }
            }
        }
    }

    downsample(hrImage, shadow, scale, HR);
}

void RegionRenderer::applyStyle2(ShadowRegion& shadow) {
    auto& cfg   = config::getConfig().terrain.shadow;
    int   scale = std::clamp(cfg.renderScale, 1, 16);

    applyShadowMap(shadow, scale);
    applyBevel(shadow, scale);
}

} // namespace map_demo
