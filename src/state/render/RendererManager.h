#pragma once

#include "data/cache/RegionCacheData.h"
#include "data/pos/RegionPos.h"


#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

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

    // 请求异步烘焙一个 region；未变脏则不会提交
    void requestBake(const std::shared_ptr<RegionCacheData>& data, const RegionPos& pos);

private:
    RendererManager();

    void workerLoop();

    struct BakeTask {
        std::weak_ptr<RegionCacheData> data;
        RegionPos                      pos;
    };

    std::thread             worker_;
    std::mutex              mutex_;
    std::condition_variable cv_;
    std::queue<BakeTask>    queue_;
    std::atomic_bool        baking_{false};
    bool                    stop_{false};
};

} // namespace map_demo