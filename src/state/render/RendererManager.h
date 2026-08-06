#pragma once

#include "data/cache/ChunkCacheData.h"
#include "data/cache/RegionCacheData.h"
#include "data/pos/ChunkPosWithDim.h"
#include "data/pos/RegionPos.h"


#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_set>

namespace map_demo {

// 渲染管理器：只负责 bake 任务的调度（工作线程 + 任务队列）
class RendererManager {
public:
    static RendererManager& getInstance();

    ~RendererManager();

    void shutdown();

    // Safe stop helper used by destructor and shutdown
    void safeStopWorker();

    // 清空队列并等待当前后台烘焙完成（世界切换前调用）
    void clearQueueAndWait();

    // 请求异步烘焙一个 region；已在队列中则不会重复提交
    void requestBake(const std::shared_ptr<RegionCacheData>& data, const RegionPos& pos);

    // 请求异步烘焙一个 chunk；未变脏或已在队列中则不会提交
    void requestChunkBake(const std::shared_ptr<ChunkCacheData>& data, const ChunkPosWithDim& pos);

private:
    RendererManager();

    void workerLoop();

    struct BakeTask {
        std::weak_ptr<RegionCacheData> data;
        RegionPos                      pos;
    };

    struct ChunkBakeTask {
        std::weak_ptr<ChunkCacheData> data;
        ChunkPosWithDim               pos;
    };

    std::thread                         worker_;
    std::mutex                          mutex_;
    std::condition_variable             cv_;
    std::queue<BakeTask>                regionQueue_;
    std::queue<ChunkBakeTask>           chunkQueue_;
    std::unordered_set<RegionPos>       queuedRegions_;
    std::unordered_set<ChunkPosWithDim> queuedChunks_;
    std::atomic_bool                   baking_{false};
    bool                               stop_{false};
};

// 阴影相关配置变化时调用；有变化则对当前维度全量 mark dirty 触发 rebake
void notifyShadowConfigChanged();

} // namespace map_demo