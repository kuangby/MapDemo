#pragma once

#include "data/cache/ChunkCacheData.h"
#include "data/cache/RegionCacheData.h"
#include "data/pos/ChunkPosWithDim.h"
#include "data/pos/RegionPos.h"
#include "data/pos/WorldPos.h"
#include <ll/api/data/KeyValueDB.h>


#include <memory>
#include <mutex>
#include <unordered_map>


namespace map_demo {
class MapCacheManager {
public:
    static MapCacheManager& getInstance();

    // Clear all cached regions (e.g. on world change)
    void clearAll();

    std::shared_ptr<RegionCacheData> getRegion(const RegionPos& pos);

    // Get or create a region
    // std::shared_ptr<RegionData> getOrCreateRegion(int regionX, int regionZ, int dim);
    std::shared_ptr<RegionCacheData> getOrCreateRegion(const RegionPos& pos);

    std::shared_ptr<ChunkCacheData> getOrCreateChunk(const ChunkPosWithDim& pos);

    // Update a single block color in cache
    void updateBlock(const WorldPos& pos, const BlockColor& color);

    // Mark a region dirty
    void markDirty(const RegionPos& pos);

    // Evict a single chunk from cache. Removes the whole region if it becomes empty.
    // void evictChunk(int chunkX, int chunkZ, int dim);

    // Evict an entire region (kept for compatibility)
    void evictRegion(const RegionPos& pos);

    // 初始化磁盘缓存，path 为 KeyValueDB 目录
    bool initializeDiskCache(const std::filesystem::path& path);

    // 磁盘缓存读写
    void               saveToDisk(const RegionPos& regionPos, std::shared_ptr<RegionCacheData> data);
    bool               loadFromDisk(const RegionPos& regionPos, std::shared_ptr<RegionCacheData> data);
    static std::string makeDiskKey(const RegionPos& regionPos);
    std::string        serializeRegionData(std::shared_ptr<RegionCacheData> data);
    bool               deserializeRegionData(std::shared_ptr<RegionCacheData> data, const std::string& blob);

    void evictRegionsOutsideRadius(ChunkPosWithDim centerChunkPos, int radiusChunks);

private:
    MapCacheManager() = default;

    std::unordered_map<RegionPos, std::shared_ptr<RegionCacheData>> regions_;
    std::mutex                                                      mutex_;

    // 磁盘缓存
    std::unique_ptr<ll::data::KeyValueDB> diskCache_;
};

} // namespace map_demo
