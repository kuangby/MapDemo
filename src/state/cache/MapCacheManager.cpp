#include "MapCacheManager.h"

#include "mod/MapDemo.h"
#include "state/pos/ChunkPosWithDim.h"
#include "state/pos/ChunkWorldPos.h"
#include "state/pos/RegionChunkPos.h"


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

std::shared_ptr<RegionCacheData> MapCacheManager::getRegion(const RegionPos& pos) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto                        it = regions_.find(pos);
    if (it == regions_.end()) return nullptr;
    return it->second;
}

std::shared_ptr<RegionCacheData> MapCacheManager::getOrCreateRegion(const RegionPos& pos) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto [newIt, inserted] = regions_.try_emplace(pos);
    if (inserted) {
        if (!loadFromDisk(pos, newIt->second)) {
            newIt->second = std::make_shared<RegionCacheData>();
        }
    }
    return newIt->second;
}

std::shared_ptr<ChunkCacheData> MapCacheManager::getOrCreateChunk(const ChunkPosWithDim& pos) {
    auto region = getOrCreateRegion(RegionPos(pos));
    return region->getOrCreateChunkData(RegionChunkPos(pos));
}

void MapCacheManager::updateBlock(const WorldPos& pos, const BlockColor& color) {
    auto regionPos  = RegionPos(pos);
    auto regionData = getOrCreateRegion(regionPos);

    auto chunk = regionData->getChunkData(RegionChunkPos(pos));
    if (chunk) {
        chunk->setColor(ChunkWorldPos(pos), color);
        regionData->markDirty();
    }
}

void MapCacheManager::markDirty(const RegionPos& pos) {
    auto data = getRegion(pos);
    if (data) data->markDirty();
}

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
