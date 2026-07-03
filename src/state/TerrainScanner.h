#pragma once

#include "state/MapCacheManager.h"

#include <ll/api/data/KeyValueDB.h>
#include <mc/world/level/BlockSource.h>
#include <mc/world/level/chunk/ChunkState.h>
#include <mc/world/level/chunk/LevelChunk.h>

#include <cstdint>
#include <limits>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace map_demo {

struct ScanChunkKey {
    int chunkX;
    int chunkZ;
    int dim;

    bool operator==(const ScanChunkKey& other) const noexcept {
        return chunkX == other.chunkX && chunkZ == other.chunkZ && dim == other.dim;
    }
};

struct ScanEntry {
    std::uint64_t nextScanFrame;
    ScanChunkKey  key;
};

struct ScanEntryCompare {
    bool operator()(const ScanEntry& a, const ScanEntry& b) const noexcept {
        if (a.nextScanFrame != b.nextScanFrame) return a.nextScanFrame < b.nextScanFrame;
        if (a.key.chunkX != b.key.chunkX) return a.key.chunkX < b.key.chunkX;
        if (a.key.chunkZ != b.key.chunkZ) return a.key.chunkZ < b.key.chunkZ;
        return a.key.dim < b.key.dim;
    }
};

} // namespace map_demo

namespace std {

template <>
struct hash<map_demo::ScanChunkKey> {
    std::size_t operator()(const map_demo::ScanChunkKey& k) const noexcept {
        std::uint64_t v = (static_cast<std::uint64_t>(static_cast<std::uint32_t>(k.chunkX)) << 32)
                        | static_cast<std::uint64_t>(static_cast<std::uint32_t>(k.chunkZ));
        return v ^ (static_cast<std::uint64_t>(k.dim) << 48);
    }
};

} // namespace std

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
    void update(BlockSource* region, int playerChunkX, int playerChunkZ, int dim, int minY, int maxY);

    // 获取当前累计帧数
    [[nodiscard]] std::uint64_t totalFrames() const { return totalFrames_; }

private:
    TerrainScanner() = default;

    // 生成以 (0,0) 为中心的螺旋 chunk 偏移
    std::vector<std::pair<int, int>> buildSpiralOffsets(int radiusChunks);

    // 根据当前玩家 chunk 更新可见集合
    void updateVisibleSet(int centerChunkX, int centerChunkZ, int dim, int scanRadiusChunks);

    // 扫描单个 chunk 并写入缓存
    void scanChunk(BlockSource* region, const ScanChunkKey& key, int minY, int maxY);

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
    int lastVisibleCenterChunkX_{std::numeric_limits<int>::max()};
    int lastVisibleCenterChunkZ_{std::numeric_limits<int>::max()};
    int lastVisibleDim_{std::numeric_limits<int>::max()};
    int lastVisibleScanRadiusChunks_{-1};

    // 优先队列：按 nextScanFrame 排序
    std::set<ScanEntry, ScanEntryCompare>                                             scanQueue_;
    std::unordered_map<ScanChunkKey, std::set<ScanEntry, ScanEntryCompare>::iterator> scanMap_;
};

} // namespace map_demo
