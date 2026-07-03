#include "state/MapCacheManager.h"

#include "mod/MapDemo.h"
#include <algorithm>


namespace map_demo {

MapCacheManager& MapCacheManager::getInstance() {
    static MapCacheManager instance;
    return instance;
}

void MapCacheManager::clearAll() {
    std::lock_guard<std::mutex> lock(mutex_);
    regions_.clear();
    diskCache_ = nullptr;
}

RegionPos MapCacheManager::worldToRegion(int worldX, int worldZ, int dim) {
    constexpr int REGION_SIZE = RegionData::SIZE;
    int           regionX     = worldX < 0 ? ((worldX + 1) / REGION_SIZE) - 1 : worldX / REGION_SIZE;
    int           regionZ     = worldZ < 0 ? ((worldZ + 1) / REGION_SIZE) - 1 : worldZ / REGION_SIZE;
    return {regionX, regionZ, dim};
}

std::shared_ptr<RegionData> MapCacheManager::getOrCreateRegion(int regionX, int regionZ, int dim) {
    return getOrCreateRegion({regionX, regionZ, dim});
}

std::shared_ptr<RegionData> MapCacheManager::getOrCreateRegion(const RegionPos& pos) {
    // std::lock_guard<std::mutex> lock(mutex_);
    // auto                        it = regions_.find(pos);
    // if (it != regions_.end()) return it->second;
    // auto [newIt, inserted] = regions_.emplace(pos, std::make_shared<RegionData>());
    // return newIt->second;
    std::lock_guard<std::mutex> lock(mutex_);
    auto [newIt, inserted] = regions_.try_emplace(pos);
    if (inserted) {
        if (!loadFromDisk(pos, newIt->second)) {
            newIt->second = std::make_shared<RegionData>();
        }
    }
    return newIt->second;
}

std::shared_ptr<ChunkData> MapCacheManager::getOrCreateChunk(const ChunkPos& pos, int dimId) {
    auto  region = getOrCreateRegion(pos.x / 16, pos.z / 16, dimId);
    auto& chunk  = region->chunkData[pos.z % 16][pos.x % 16];
    if (!chunk) chunk = std::make_shared<ChunkData>();
    return chunk;
}

void MapCacheManager::updateBlock(int worldX, int worldZ, int dim, BlockColor color) {
    auto pos  = worldToRegion(worldX, worldZ, dim);
    auto data = getOrCreateRegion(pos);

    constexpr int REGION_SIZE = RegionData::SIZE;
    int           localX      = worldX - (pos.x * REGION_SIZE);
    int           localZ      = worldZ - (pos.z * REGION_SIZE);
    if (localX < 0) localX += REGION_SIZE;
    if (localZ < 0) localZ += REGION_SIZE;

    localX = std::clamp(localX, 0, REGION_SIZE - 1);
    localZ = std::clamp(localZ, 0, REGION_SIZE - 1);

    data->setPixel(localX, localZ, color);
    std::unique_lock<std::shared_mutex> lock(data->mutex_);
    data->dirty = true;
}

void MapCacheManager::markDirty(int regionX, int regionZ, int dim) {
    auto data = getOrCreateRegion(regionX, regionZ, dim);
    if (data) {
        std::unique_lock<std::shared_mutex> lock(data->mutex_);
        data->dirty = true;
    }
}

void MapCacheManager::evictRegion(int regionX, int regionZ, int dim) { evictRegion({regionX, regionZ, dim}); }

void MapCacheManager::evictRegion(const RegionPos& pos) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto                        it = regions_.find(pos);
    if (it == regions_.end()) return;
    saveToDisk(pos, it->second);
    regions_.erase(it);
}

// void MapCacheManager::evictChunk(int chunkX, int chunkZ, int dim) {
//     auto pos = worldToRegion(chunkX * 16, chunkZ * 16, dim);

//     std::lock_guard<std::mutex> lock(mutex_);
//     auto                        it = regions_.find(pos);
//     if (it == regions_.end()) return;

//     int regionMinChunkX = pos.x * RegionData::CHUNKS;
//     int regionMinChunkZ = pos.z * RegionData::CHUNKS;
//     int localChunkX     = chunkX - regionMinChunkX;
//     int localChunkZ     = chunkZ - regionMinChunkZ;
//     if (localChunkX < 0 || localChunkX >= RegionData::CHUNKS || localChunkZ < 0 || localChunkZ >= RegionData::CHUNKS)
//     {
//         return;
//     }

//     it->second->clearChunk(localChunkX, localChunkZ);
//     if (it->second->isEmpty()) {
//         regions_.erase(it);
//     }
// }

bool MapCacheManager::initializeDiskCache(const std::filesystem::path& path) {
    try {
        diskCache_ = std::make_unique<ll::data::KeyValueDB>(path);
        return true;
    } catch (const std::exception& e) {
        MapDemo::getInstance().getSelf().getLogger().error("MapCacheManager: failed to init disk cache: {}", e.what());
        diskCache_ = nullptr;
        return false;
    }
}
} // namespace map_demo
