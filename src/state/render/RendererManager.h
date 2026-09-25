#pragma once

#include "data/cache/ChunkCacheData.h"
#include "data/cache/RegionCacheData.h"
#include "data/pos/ChunkPosWithDim.h"
#include "data/pos/RegionPos.h"


#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <unordered_map>
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
    // softOnly：柔化级重烘（跳过射线采样）；队列中已有 soft 任务时 full 请求会升级该任务
    void requestChunkBake(const std::shared_ptr<ChunkCacheData>& data, const ChunkPosWithDim& pos, bool softOnly = false);

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
        bool                          softOnly;
    };

    std::thread                                worker_;
    std::mutex                                 mutex_;
    std::condition_variable                    cv_;
    std::queue<BakeTask>                       regionQueue_;
    std::queue<ChunkBakeTask>                  chunkQueue_;
    std::unordered_set<RegionPos>              queuedRegions_;
    std::unordered_map<ChunkPosWithDim, bool>  queuedChunks_; // value: softOnly
    std::atomic_bool                           baking_{false};
    bool                                       stop_{false};
};

} // namespace map_demo