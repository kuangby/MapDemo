#include "RendererManager.h"

#include "config/Config.h"
#include "data/cache/MapCacheManager.h"
#include "mod/MapDemo.h"
#include "state/MapState.h"
#include "state/render/ChunkShadowRenderer.h"
#include "state/render/RegionShadowRenderer.h"


#include <chrono>
#include <memory>
#include <mutex>

namespace map_demo {

using Clock = std::chrono::high_resolution_clock;

RendererManager& RendererManager::getInstance() {
    static RendererManager instance;
    return instance;
}

RendererManager::RendererManager() : worker_([this] { workerLoop(); }) {}

RendererManager::~RendererManager() {
    // During DLL unload the runtime may already be tearing down.
    // Avoid any logger access or object recreation here.
    safeStopWorker();
}

void RendererManager::safeStopWorker() {
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

void RendererManager::shutdown() { safeStopWorker(); }

void RendererManager::clearQueueAndWait() {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        stop_ = true;
        while (!regionQueue_.empty()) {
            regionQueue_.pop();
        }
        while (!chunkQueue_.empty()) {
            chunkQueue_.pop();
        }
        queuedChunks_.clear();
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

void RendererManager::requestBake(const std::shared_ptr<RegionCacheData>& data, const RegionPos& pos) {
    if (!data) return;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!data->isBakedDirty()) return;
        regionQueue_.push(BakeTask{data, pos});
    }
    cv_.notify_one();
}

void RendererManager::requestChunkBake(const std::shared_ptr<ChunkCacheData>& data, const ChunkPosWithDim& pos) {
    if (!data) return;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!data->isBakedDirty()) return;
        if (!queuedChunks_.insert(pos).second) return;
        chunkQueue_.push(ChunkBakeTask{data, pos});
    }
    cv_.notify_one();
}

void RendererManager::workerLoop() {
    while (true) {
        BakeTask      regionTask;
        ChunkBakeTask chunkTask;
        bool          isChunkTask = false;
        {
            std::unique_lock<std::mutex> lock(mutex_);
            cv_.wait(lock, [this] { return stop_ || !regionQueue_.empty() || !chunkQueue_.empty(); });
            if (stop_ && regionQueue_.empty() && chunkQueue_.empty()) return;
            if (!regionQueue_.empty()) {
                regionTask = regionQueue_.front();
                regionQueue_.pop();
            } else {
                chunkTask = chunkQueue_.front();
                chunkQueue_.pop();
                queuedChunks_.erase(chunkTask.pos);
                isChunkTask = true;
            }
        }

        baking_.store(true, std::memory_order_release);
        auto t0 = Clock::now();
        if (isChunkTask) {
            auto data = chunkTask.data.lock();
            if (!data) {
                baking_.store(false, std::memory_order_release);
                continue;
            }
            ChunkShadowRenderer renderer(chunkTask.pos);
            renderer.bake(data);
            data->takeBakedDirty();
            if (auto region = MapCacheManager::getInstance().getRegion(RegionPos(chunkTask.pos))) {
                region->markEverBaked();
            }
            auto us = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - t0).count();
            baking_.store(false, std::memory_order_release);

            static int s_workerChunkLog = 0;
            if ((++s_workerChunkLog % 100) == 0 || us > 50000) {
                MapDemo::getInstance().getSelf().getLogger().debug(
                    "RendererManager::worker bake chunk=({},{}), dim={}, time={}us",
                    chunkTask.pos.x,
                    chunkTask.pos.z,
                    chunkTask.pos.dimId,
                    us
                );
            }
        } else {
            auto data = regionTask.data.lock();
            if (!data) {
                baking_.store(false, std::memory_order_release);
                continue;
            }
            RegionShadowRenderer renderer(regionTask.pos);
            renderer.bake(data);
            if (auto region = MapCacheManager::getInstance().getRegion(regionTask.pos)) {
                region->markEverBaked();
            }
            auto us = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - t0).count();
            baking_.store(false, std::memory_order_release);

            static int s_workerLog = 0;
            if ((++s_workerLog % 10) == 0 || us > 50000) {
                MapDemo::getInstance().getSelf().getLogger().debug(
                    "RendererManager::worker bake region=({},{}), dim={}, time={}us",
                    regionTask.pos.x,
                    regionTask.pos.z,
                    regionTask.pos.dimId,
                    us
                );
            }
        }
    }
}

void notifyShadowConfigChanged() {
    auto& shadow = config::getConfig().terrain.shadow;

    struct ShadowSnapshot {
        int   renderStyle;
        int   renderScale;
        int   pcfRadius;
        int   shadowLevel;
        float lightAzimuth;
        float lightZenith;
        bool  transparentWater;

        [[nodiscard]] bool operator==(const ShadowSnapshot&) const = default;
    };

    static ShadowSnapshot last{
        shadow.renderStyle,
        shadow.renderScale,
        shadow.pcfRadius,
        shadow.shadowLevel,
        shadow.lightAzimuth,
        shadow.lightZenith,
        shadow.transparentWater
    };

    ShadowSnapshot current{
        shadow.renderStyle,
        shadow.renderScale,
        shadow.pcfRadius,
        shadow.shadowLevel,
        shadow.lightAzimuth,
        shadow.lightZenith,
        shadow.transparentWater
    };

    if (current == last) return;
    last = current;

    auto& state = MapState::getInstance();
    if (!state.hasPlayer()) return;
    MapCacheManager::getInstance().markAllDirty(state.dimensionId());
}

} // namespace map_demo