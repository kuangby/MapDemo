#include "MapCacheManager.h"

#include "data/pos/ChunkPosWithDim.h"
#include "data/pos/ChunkWorldPos.h"
#include "data/pos/RegionChunkPos.h"
#include "mod/MapDemo.h"


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

std::shared_ptr<ChunkCacheData> MapCacheManager::getChunk(const ChunkPosWithDim& pos) {
    auto region = getRegion(RegionPos(pos));
    if (!region) return nullptr;
    return region->getChunkData(RegionChunkPos(pos));
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

// std::shared_ptr<ChunkCacheData> MapCacheManager::getOrCreateChunk(const ChunkPosWithDim& pos) {
//     auto region = getOrCreateRegion(RegionPos(pos));
//     return region->getOrCreateChunkData(RegionChunkPos(pos));
// }

// void MapCacheManager::updateBlock(const WorldPos& pos, const BlockColor& color) {
//     auto regionPos  = RegionPos(pos);
//     auto regionData = getOrCreateRegion(regionPos);

//     auto chunk = regionData->getChunkData(RegionChunkPos(pos));
//     if (chunk) {
//         chunk->setColor(ChunkWorldPos(pos), color);
//         regionData->markBakedDirty();
//     }
// }

// void MapCacheManager::markDirty(const RegionPos& pos) {
//     auto data = getRegion(pos);
//     if (data) data->markBakedDirty();
// }

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

void MapCacheManager::evictRegionsOutsideRadius(ChunkPosWithDim centerChunkPos, int radiusChunks) {
    std::lock_guard<std::mutex> lock(mutex_);
    const int threshold  = 2 * radiusChunks + 8;
    const int threshold2 = threshold * threshold;

    for (auto it = regions_.begin(); it != regions_.end();) {
        const auto& regionPos = it->first;
        if (regionPos.dimId != centerChunkPos.dimId) {
            ++it;
            continue;
        }

        int regionCenterChunkX = regionPos.x * 16 + 8;
        int regionCenterChunkZ = regionPos.z * 16 + 8;
        int dx                 = regionCenterChunkX - centerChunkPos.x;
        int dz                 = regionCenterChunkZ - centerChunkPos.z;

        if (dx * dx + dz * dz > threshold2) {
            saveToDisk(regionPos, it->second);
            it = regions_.erase(it);
        } else {
            ++it;
        }
    }
}

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
