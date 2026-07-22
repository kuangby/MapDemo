#include "RendererManager.h"

#include "mod/MapDemo.h"
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
        while (!queue_.empty()) {
            queue_.pop();
        }
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
        queue_.push(BakeTask{data, pos});
    }
    cv_.notify_one();
}

void RendererManager::workerLoop() {
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
        auto                 t0 = Clock::now();
        RegionShadowRenderer renderer(task.pos);
        renderer.bake(data);
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - t0).count();
        baking_.store(false, std::memory_order_release);

        static int s_workerLog = 0;
        if ((++s_workerLog % 10) == 0 || us > 50000) {
            MapDemo::getInstance().getSelf().getLogger().debug(
                "RendererManager::worker bake region=({},{}), dim={}, time={}us",
                task.pos.x,
                task.pos.z,
                task.pos.dimId,
                us
            );
        }
    }
}

} // namespace map_demo