#pragma once

#include "state/MapCacheManager.h"

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_set>
#include <vector>

namespace map_demo {

// 单个方块的渲染信息（类似 BedrockMap 的 BlockTipsInfo）
struct BlockRenderInfo {
    std::string  blockName;          // 显示用的方块名
    std::string  solidBlockName;     // 水下固体方块名
    std::uint8_t waterDepth{0};      // 0 = 无水
    BlockColor   waterSurfaceColor{}; // 水面颜色（已群系混合）
    int16_t      height{-128};       // 表面高度（含水面）
    int16_t      solidHeight{-128};  // 固体地面高度
    bool         hasData{false};     // 是否有有效高度数据
};

// 用于阴影烘焙的区域辅助结构，16x16 chunks
struct ShadowRegion {
    static constexpr int SIZE        = RegionData::SIZE;          // 256
    static constexpr int CHUNKS      = RegionData::CHUNKS;        // 16
    static constexpr int PIXELS      = SIZE * SIZE;

    std::vector<BlockColor> terrain;       // 256x256 RGBA
    std::vector<BlockRenderInfo> info;     // 256x256 per-pixel info

    ShadowRegion() : terrain(PIXELS), info(PIXELS) {}

    [[nodiscard]] BlockColor getPixel(int x, int z) const { return terrain[z * SIZE + x]; }
    void setPixel(int x, int z, BlockColor c) { terrain[z * SIZE + x] = c; }

    [[nodiscard]] const BlockRenderInfo& getInfo(int x, int z) const { return info[z * SIZE + x]; }
    void setInfo(int x, int z, const BlockRenderInfo& i) { info[z * SIZE + x] = i; }

    [[nodiscard]] int16_t getHeight(int x, int z) const { return info[z * SIZE + x].height; }
    [[nodiscard]] int16_t getSolidHeight(int x, int z) const { return info[z * SIZE + x].solidHeight; }
    [[nodiscard]] bool hasData(int x, int z) const { return info[z * SIZE + x].height != -128; }
};

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
    void requestBake(const std::shared_ptr<RegionData>& data, const RegionPos& pos, int dim);

    // 同步烘焙（紧急情况或退化为 Style 0/1 时可用）
    void bake(const RegionData* data, BlockColor* output, int dim);

private:
    RegionRenderer();

    void workerLoop();

    // 加锁快照一份 RegionData 到 ShadowRegion，然后离线烘焙
    void snapshotAndBake(const std::shared_ptr<RegionData>& data, int dim);

    void copyRegionToShadow(const RegionData* data, ShadowRegion& shadow, int dim);

    void applyStyle1(ShadowRegion& shadow);
    void applyStyle2(ShadowRegion& shadow);
    void applyWaterOverlay(ShadowRegion& shadow);
    void applyShadowMap(ShadowRegion& shadow, int scale);
    void applyBevel(ShadowRegion& shadow, int scale);

    // 上采样辅助
    void upscale(const ShadowRegion& src, std::vector<BlockColor>& dst, int scale, int dstSize);
    void downsample(const std::vector<BlockColor>& src, ShadowRegion& dst, int scale, int srcSize);

    struct BakeTask {
        std::weak_ptr<RegionData> data;
        int                        dim{0};
        RegionPos                  pos;
    };

    std::thread worker_;
    std::mutex mutex_;
    std::condition_variable cv_;
    std::queue<BakeTask> queue_;
    std::unordered_set<RegionPos, std::hash<RegionPos>> pending_;
    std::atomic_bool baking_{false};
    bool stop_{false};
};

} // namespace map_demo