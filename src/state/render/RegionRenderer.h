#pragma once

#include "data/cache/RegionCacheData.h"
#include "data/pos/RegionPos.h"
#include "data/shadowRender/ShadowRenderData.h"


#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_set>

namespace map_demo {

// 区域渲染器：负责把 RegionData 的地形颜色烘焙成带阴影的最终图像
class RegionRenderer {
public:
    static RegionRenderer& getInstance();

    ~RegionRenderer();

    void shutdown();

    // Safe stop helper used by destructor and shutdown
    void safeStopWorker();

    // 清空队列并等待当前后台烘焙完成（世界切换前调用）
    void clearQueueAndWait();

    // 请求异步烘焙一个 region；如果烘焙中或未变脏不会重复提交
    void requestBake(const std::shared_ptr<RegionCacheData>& data, const RegionPos& pos, int dim);

    // // 同步烘焙（紧急情况或退化为 Style 0/1 时可用）
    // void bake(const RegionCacheData* data, BlockColor* output, int dim);

private:
    RegionRenderer();

    void workerLoop();

    // 加锁快照一份 RegionData 到 ShadowRegion，然后离线烘焙
    void snapshotAndBake(const std::shared_ptr<RegionCacheData>& data, const RegionPos& pos, int dim);

    // void copyRegionToShadow(const RegionCacheData* data, ShadowRegion& shadow, int dim);

    void applyStyle1(ShadowRenderData& shadow);
    void applyStyle2(ShadowRenderData& shadow);
    void applyWaterOverlay(ShadowRenderData& shadow);
    void applyShadowMap(ShadowRenderData& shadow, int scale);
    void applyBevel(ShadowRenderData& shadow, int scale);

    struct BakeTask {
        std::weak_ptr<RegionCacheData> data;
        int                            dim{0};
        RegionPos                      pos;
    };

    std::thread                                         worker_;
    std::mutex                                          mutex_;
    std::condition_variable                             cv_;
    std::queue<BakeTask>                                queue_;
    std::unordered_set<RegionPos, std::hash<RegionPos>> pending_;
    std::atomic_bool                                    baking_{false};
    bool                                                stop_{false};
};

} // namespace map_demo