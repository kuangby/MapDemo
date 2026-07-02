#include "state/RegionRenderer.h"

#include "config/Config.h"
#include "mod/MapDemo.h"

#include <algorithm>
#include <chrono>
#include <cmath>

namespace map_demo {

using Clock = std::chrono::high_resolution_clock;

namespace {

inline int clamp255(int v) { return std::clamp(v, 0, 255); }

inline BlockColor multiplyColor(BlockColor c, float factor) {
    return BlockColor{
        static_cast<std::uint8_t>(clamp255(static_cast<int>(c.r * factor))),
        static_cast<std::uint8_t>(clamp255(static_cast<int>(c.g * factor))),
        static_cast<std::uint8_t>(clamp255(static_cast<int>(c.b * factor))),
        c.a
    };
}

inline BlockColor blendColors(BlockColor base, BlockColor overlay, float overlayFactor) {
    float baseFactor = 1.0f - overlayFactor;
    return BlockColor{
        static_cast<std::uint8_t>(clamp255(static_cast<int>(base.r * baseFactor + overlay.r * overlayFactor))),
        static_cast<std::uint8_t>(clamp255(static_cast<int>(base.g * baseFactor + overlay.g * overlayFactor))),
        static_cast<std::uint8_t>(clamp255(static_cast<int>(base.b * baseFactor + overlay.b * overlayFactor))),
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

void RegionRenderer::requestBake(const std::shared_ptr<RegionData>& data, const RegionPos& pos, int dim) {
    if (!data) return;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!data->bakedDirty) return;
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
        snapshotAndBake(data, task.dim);
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

void RegionRenderer::snapshotAndBake(const std::shared_ptr<RegionData>& data, int /*dim*/) {
    if (!data) return;

    // Snapshot raw data under lock, then bake offline without holding the lock
    ShadowRegion shadow;
    {
        std::shared_lock<std::shared_mutex> lock(data->mutex_);
        if (!data->bakedDirty) return;
        shadow.terrain = std::vector<BlockColor>(RegionData::PIXELS);
        shadow.info    = std::vector<BlockRenderInfo>(RegionData::PIXELS);
        for (int z = 0; z < RegionData::SIZE; ++z) {
            for (int x = 0; x < RegionData::SIZE; ++x) {
                int idx             = z * RegionData::SIZE + x;
                shadow.terrain[idx] = BlockColor{
                    data->colors[idx * 4 + 0],
                    data->colors[idx * 4 + 1],
                    data->colors[idx * 4 + 2],
                    data->colors[idx * 4 + 3]
                };
                BlockRenderInfo bri{};
                bri.height      = data->heights[idx];
                bri.solidHeight = data->solidHeights[idx];
                bri.waterDepth  = data->waterDepths[idx];
                bri.hasData     = (bri.height > -128);
                if (bri.waterDepth > 0) bri.waterSurfaceColor = BlockColor{64, 94, 241, 255};
                shadow.info[idx] = bri;
            }
        }
    }

    auto& cfg = config::getConfig().terrain.shadow;
    if (cfg.renderStyle == 1) {
        if (cfg.transparentWater) applyWaterOverlay(shadow);
        applyStyle1(shadow);
    } else if (cfg.renderStyle == 2) {
        applyStyle2(shadow);
    } else {
        if (cfg.transparentWater) applyWaterOverlay(shadow);
    }

    // Write result back
    {
        std::unique_lock<std::shared_mutex> lock(data->mutex_);
        for (int z = 0; z < RegionData::SIZE; ++z) {
            for (int x = 0; x < RegionData::SIZE; ++x) {
                int  idx                       = z * RegionData::SIZE + x;
                auto c                         = shadow.terrain[idx];
                data->bakedColors[idx * 4 + 0] = c.r;
                data->bakedColors[idx * 4 + 1] = c.g;
                data->bakedColors[idx * 4 + 2] = c.b;
                data->bakedColors[idx * 4 + 3] = c.a;
            }
        }
        data->bakedDirty = false;
    }
}

void RegionRenderer::copyRegionToShadow(const RegionData* data, ShadowRegion& shadow, int /*dim*/) {
    for (int z = 0; z < ShadowRegion::SIZE; ++z) {
        for (int x = 0; x < ShadowRegion::SIZE; ++x) {
            shadow.setPixel(x, z, data->getPixel(x, z));

            BlockRenderInfo bri{};
            bri.height      = data->getHeight(x, z);
            bri.solidHeight = data->getSolidHeight(x, z);
            bri.waterDepth  = data->getWaterDepth(x, z);
            bri.hasData     = (bri.height > -128);

            if (bri.waterDepth > 0) {
                bri.waterSurfaceColor = BlockColor{64, 94, 241, 255};
            }

            shadow.setInfo(x, z, bri);
        }
    }
}

void RegionRenderer::bake(const RegionData* data, BlockColor* output, int dim) {
    if (!data || !output) return;
    auto t0 = Clock::now();

    ShadowRegion shadow;
    copyRegionToShadow(data, shadow, dim);

    auto& cfg = config::getConfig().terrain.shadow;
    if (cfg.renderStyle == 1) {
        if (cfg.transparentWater) applyWaterOverlay(shadow);
        applyStyle1(shadow);
    } else if (cfg.renderStyle == 2) {
        applyStyle2(shadow);
    } else {
        if (cfg.transparentWater) applyWaterOverlay(shadow);
    }

    for (int z = 0; z < ShadowRegion::SIZE; ++z) {
        for (int x = 0; x < ShadowRegion::SIZE; ++x) {
            output[z * ShadowRegion::SIZE + x] = shadow.getPixel(x, z);
        }
    }

    auto totalUs = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - t0).count();
    if (totalUs > 30000) {
        MapDemo::getInstance().getSelf().getLogger().debug(
            "RegionRenderer::bake sync slow style={}, time={}us",
            cfg.renderStyle,
            totalUs
        );
    }
}

// Style 1: simple heightmap gradient shadow, light from northwest
void RegionRenderer::applyStyle1(ShadowRegion& shadow) {
    auto& cfg   = config::getConfig().terrain.shadow;
    int   level = cfg.shadowLevel;
    if (level <= 0) level = 100;

    for (int z = 0; z < ShadowRegion::SIZE; ++z) {
        for (int x = 0; x < ShadowRegion::SIZE; ++x) {
            if (!shadow.hasData(x, z)) continue;

            int16_t cur = shadow.getHeight(x, z);
            int16_t sum = cur * 2;
            if (x == 0 && z != 0) {
                sum = shadow.getHeight(x, z - 1) * 2;
            } else if (x != 0 && z == 0) {
                sum = shadow.getHeight(x - 1, z) * 2;
            } else if (x != 0 && z != 0) {
                sum = shadow.getHeight(x, z - 1) + shadow.getHeight(x - 1, z);
            }

            BlockColor c = shadow.getPixel(x, z);
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
            shadow.setPixel(x, z, c);
        }
    }
}

void RegionRenderer::applyWaterOverlay(ShadowRegion& shadow) {
    for (int z = 0; z < ShadowRegion::SIZE; ++z) {
        for (int x = 0; x < ShadowRegion::SIZE; ++x) {
            const auto& info = shadow.getInfo(x, z);
            if (info.waterDepth == 0) continue;

            float opacity = std::min(0.15f * static_cast<float>(info.waterDepth), 0.85f);
            shadow.setPixel(x, z, blendColors(shadow.getPixel(x, z), info.waterSurfaceColor, opacity));
        }
    }
}

void RegionRenderer::upscale(const ShadowRegion& src, std::vector<BlockColor>& dst, int scale, int dstSize) {
    dst.resize(dstSize * dstSize);
    for (int z = 0; z < dstSize; ++z) {
        int sz = std::min(z / scale, ShadowRegion::SIZE - 1);
        for (int x = 0; x < dstSize; ++x) {
            int sx               = std::min(x / scale, ShadowRegion::SIZE - 1);
            dst[z * dstSize + x] = src.getPixel(sx, sz);
        }
    }
}

void RegionRenderer::downsample(const std::vector<BlockColor>& src, ShadowRegion& dst, int scale, int srcSize) {
    for (int z = 0; z < ShadowRegion::SIZE; ++z) {
        for (int x = 0; x < ShadowRegion::SIZE; ++x) {
            int r = 0, g = 0, b = 0, a = 0;
            for (int dy = 0; dy < scale; ++dy) {
                int sy = z * scale + dy;
                if (sy >= srcSize) continue;
                for (int dx = 0; dx < scale; ++dx) {
                    int sx = x * scale + dx;
                    if (sx >= srcSize) continue;
                    auto c  = src[sy * srcSize + sx];
                    r      += c.r;
                    g      += c.g;
                    b      += c.b;
                    a      += c.a;
                }
            }
            int samples = scale * scale;
            dst.setPixel(
                x,
                z,
                BlockColor{
                    static_cast<std::uint8_t>(r / samples),
                    static_cast<std::uint8_t>(g / samples),
                    static_cast<std::uint8_t>(b / samples),
                    static_cast<std::uint8_t>(a / samples)
                }
            );
        }
    }
}

void RegionRenderer::applyShadowMap(ShadowRegion& shadow, int scale) {
    auto& cfg = config::getConfig().terrain.shadow;

    constexpr float kShadowDarkness = 0.52f;
    constexpr int   kMaxSteps       = 192;

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

    const int HR = ShadowRegion::SIZE * scale;

    auto coarseH = [&](int hi, int hj, const ShadowRegion& s) -> float {
        int bi = std::clamp(hi / scale, 0, ShadowRegion::SIZE - 1);
        int bj = std::clamp(hj / scale, 0, ShadowRegion::SIZE - 1);
        return s.getHeight(bi, bj);
    };

    std::vector<float> shadowMap(HR * HR, 1.0f);
    for (int hj = 0; hj < HR; ++hj) {
        for (int hi = 0; hi < HR; ++hi) {
            float h = coarseH(hi, hj, shadow);
            if (h <= -128) continue;

            float fx = static_cast<float>(hi) + 0.5f;
            float fy = static_cast<float>(hj) + 0.5f;
            for (int s = 1; s <= kMaxSteps; ++s) {
                int si = static_cast<int>(fx + s * sdx);
                int sj = static_cast<int>(fy + s * sdz);
                if (si < 0 || si >= HR || sj < 0 || sj >= HR) break;
                float nh = coarseH(si, sj, shadow);
                if (nh <= -128) break;
                if (nh > h + s * dzPerStep + 0.1f) {
                    shadowMap[hj * HR + hi] = kShadowDarkness;
                    break;
                }
            }
        }
    }

    std::vector<BlockColor> hrImage;
    upscale(shadow, hrImage, scale, HR);

    const int pcfRadius = std::clamp(cfg.pcfRadius, 0, 8);
    for (int hj = 0; hj < HR; ++hj) {
        for (int hi = 0; hi < HR; ++hi) {
            if (coarseH(hi, hj, shadow) <= -128) continue;

            int i0 = std::max(0, hi - pcfRadius);
            int i1 = std::min(HR - 1, hi + pcfRadius);
            int j0 = std::max(0, hj - pcfRadius);
            int j1 = std::min(HR - 1, hj + pcfRadius);

            float sum   = 0.0f;
            int   count = 0;
            for (int sj = j0; sj <= j1; ++sj) {
                for (int si = i0; si <= i1; ++si) {
                    if (coarseH(si, sj, shadow) <= -128) continue;
                    sum += shadowMap[sj * HR + si];
                    ++count;
                }
            }
            if (count == 0) continue;
            float shadowFactor = sum / count;
            if (shadowFactor >= 1.0f) continue;

            hrImage[hj * HR + hi] = multiplyColor(hrImage[hj * HR + hi], shadowFactor);
        }
    }

    downsample(hrImage, shadow, scale, HR);
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

    if (cfg.transparentWater) applyWaterOverlay(shadow);

    applyShadowMap(shadow, scale);
    applyBevel(shadow, scale);
}

} // namespace map_demo
