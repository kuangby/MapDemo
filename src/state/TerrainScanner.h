#pragma once

#include "data/pos/ChunkPosWithDim.h"

#include <ll/api/data/KeyValueDB.h>
#include <mc/world/level/BlockSource.h>
#include <mc/world/level/chunk/ChunkState.h>
#include <mc/world/level/chunk/LevelChunk.h>

#include <cstdint>
#include <set>
#include <unordered_map>
#include <vector>

namespace map_demo {

struct ScanEntry {
    std::uint64_t   nextScanFrame = 0;
    ChunkPosWithDim key;
};

struct ScanEntryCompare {
    bool operator()(const ScanEntry& a, const ScanEntry& b) const noexcept {
        if (a.nextScanFrame != b.nextScanFrame) return a.nextScanFrame < b.nextScanFrame;
        if (a.key.x != b.key.x) return a.key.x < b.key.x;
        if (a.key.z != b.key.z) return a.key.z < b.key.z;
        return a.key.dimId < b.key.dimId;
    }
};

} // namespace map_demo

namespace map_demo {

// 地形扫描调度器
// - 以 chunk 为粒度管理扫描任务
// - 玩家视野内的 chunk 按螺旋顺序优先扫描（中心优先）
// - 每个 chunk 记录上次扫描帧号，满足 rescanIntervalFrames 才再次扫描
// - 离开视野 2 倍半径后，从内存和磁盘中移除缓存
class TerrainScanner {
public:
    static TerrainScanner& getInstance();

    // 关闭时清理资源
    void shutdown();

    // 玩家进入/离开世界时清空状态
    void clearState();

    // 每帧调用一次，处理待扫描任务
    void update(BlockSource* region, const ChunkPosWithDim& playerChunkPos);

    // 获取当前累计帧数
    [[nodiscard]] std::uint64_t totalFrames() const { return totalFrames_; }

private:
    TerrainScanner() = default;

    // 生成以 (0,0) 为中心的螺旋 chunk 偏移
    std::vector<std::pair<int, int>> buildSpiralOffsets(int radiusChunks);

    // 根据当前玩家 chunk 更新可见集合
    void updateVisibleSet(const ChunkPosWithDim& playerChunkPos, int scanRadiusChunks);

    // 扫描单个 chunk 并写入缓存
    void scanChunk(BlockSource* region, const ChunkPosWithDim& key) const;

    // 序列化/反序列化单个 chunk 的颜色数据
    // std::string serializeChunk(const RegionData* data, int chunkLocalX, int chunkLocalZ);
    // void        deserializeChunk(RegionData* data, int chunkLocalX, int chunkLocalZ, const std::string& blob);

    // 磁盘缓存读写
    // void saveChunkToDisk(const ScanChunkKey& key, const RegionData* data, int localChunkX, int localChunkZ);
    // bool loadChunkFromDisk(const ScanChunkKey& key, RegionData* data, int localChunkX, int localChunkZ);

    // 生成 KeyValueDB 的 key
    // static std::string makeDiskKey(const ScanChunkKey& key);

    // 判断 chunk 是否已加载
    static bool isChunkLoaded(LevelChunk* chunk);

    std::uint64_t totalFrames_{0};

    int scanRadiusChunks_{0};

    // 上次 updateVisibleSet 的状态，用于避免每帧重复遍历
    ChunkPosWithDim lastVisibleCenterChunkPos    = {0, 0, -1};
    int             lastVisibleScanRadiusChunks_ = -1;

    // 优先队列：按 nextScanFrame 排序
    std::set<ScanEntry, ScanEntryCompare>                                                scanQueue_;
    std::unordered_map<ChunkPosWithDim, std::set<ScanEntry, ScanEntryCompare>::iterator> scanMap_;
};

} // namespace map_demo
