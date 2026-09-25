#include "RendererManager.h"

#include "config/Config.h"
#include "data/cache/MapCacheManager.h"
#include "state/MapState.h"
#include "state/render/ChunkShadowRenderer.h"
#include "state/render/RegionShadowRenderer.h"


#include <memory>
#include <mutex>

namespace map_demo {

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
        queuedRegions_.clear();
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
        if (!queuedRegions_.insert(pos).second) return;
        regionQueue_.push(BakeTask{data, pos});
    }
    cv_.notify_one();
}

void RendererManager::requestChunkBake(
    const std::shared_ptr<ChunkCacheData>& data,
    const ChunkPosWithDim&                 pos,
    bool                                   softOnly
) {
    if (!data) return;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (softOnly ? !data->isBakedSoftDirty() : !data->isBakedDirty()) {
            // 脏标记丢失：调度方认为该 chunk 脏，但标记已被消费，阴影可能残留
            return;
        }
        auto [it, inserted] = queuedChunks_.try_emplace(pos, softOnly);
        if (!inserted) {
            // 已有 full 任务在队（full 涵盖 soft），或同级重复提交：忽略
            if (!it->second || softOnly) return;
            // soft → full 升级：补投 full 任务；旧 soft 任务出队时会因 full 脏标记被跳过
            it->second = false;
            chunkQueue_.push(ChunkBakeTask{data, pos, false});
            cv_.notify_one();
            return;
        }
        chunkQueue_.push(ChunkBakeTask{data, pos, softOnly});
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
                queuedRegions_.erase(regionTask.pos);
            } else {
                chunkTask = chunkQueue_.front();
                chunkQueue_.pop();
                queuedChunks_.erase(chunkTask.pos);
                isChunkTask = true;
            }
        }

        baking_.store(true, std::memory_order_release);
        if (isChunkTask) {
            auto data = chunkTask.data.lock();
            if (!data) {
                baking_.store(false, std::memory_order_release);
                continue;
            }
            ChunkShadowRenderer renderer(chunkTask.pos);
            if (chunkTask.softOnly) {
                // 存在 full 脏标记时柔化级重烘无意义（full 任务会涵盖），直接跳过
                if (data->isBakedDirty()) {
                    baking_.store(false, std::memory_order_release);
                    continue;
                }
                auto epoch = data->getBakedSoftDirtyEpoch();
                renderer.bake(data, true);
                data->takeBakedSoftDirtyIfEpoch(epoch);
            } else {
                auto epoch  = data->getBakedDirtyEpoch();
                auto epochS = data->getBakedSoftDirtyEpoch();
                renderer.bake(data, false);
                // bake 期间被重新标脏（epoch 变化）时保留脏标记，并重新武装 region 防抖以触发重烘
                if (!data->takeBakedDirtyIfEpoch(epoch)) {
                    if (auto region = MapCacheManager::getInstance().getRegion(RegionPos(chunkTask.pos))) {
                        region->markBakedDirty();
                    }
                }
                // full 烘已涵盖柔化；bake 期间新产生的 soft 标脏（epoch 变化）保留
                data->takeBakedSoftDirtyIfEpoch(epochS);
            }
            if (auto region = MapCacheManager::getInstance().getRegion(RegionPos(chunkTask.pos))) {
                region->markEverBaked();
            }
            baking_.store(false, std::memory_order_release);
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
            baking_.store(false, std::memory_order_release);
        }
    }
}

} // namespace map_demo