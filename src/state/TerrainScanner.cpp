#include "state/TerrainScanner.h"

#include "config/Config.h"
#include "mod/MapDemo.h"
#include "pos/ChunkPosWithDim.h"
#include "pos/ChunkWorldPos.h"
#include "pos/RegionChunkPos.h"
#include "pos/RegionPos.h"
#include "state/BlockColorManager.h"
#include "state/TerrainColorUtils.h"
#include "state/cache/MapCacheManager.h"

#include "mc/world/level/dimension/Dimension.h"
#include <mc/world/level/BlockSource.h>
#include <mc/world/level/ChunkBlockPos.h>
#include <mc/world/level/ChunkLocalHeight.h>
#include <mc/world/level/biome/Biome.h>
#include <mc/world/level/block/Block.h>


#include <algorithm>
#include <chrono>
#include <cmath>

namespace map_demo {

using Clock = std::chrono::high_resolution_clock;

namespace {

struct ChunkRect {
    int xMin;
    int xMax;
    int zMin;
    int zMax;
};

// 将矩形 A 减去矩形 B，返回 A\B 的矩形列表
std::vector<ChunkRect> subtractRects(const ChunkRect& A, const ChunkRect& B) {
    std::vector<ChunkRect> result;
    // A 在 B 左侧的部分
    if (A.xMin < B.xMin) {
        result.push_back({A.xMin, B.xMin - 1, A.zMin, A.zMax});
    }
    // A 在 B 右侧的部分
    if (A.xMax > B.xMax) {
        result.push_back({B.xMax + 1, A.xMax, A.zMin, A.zMax});
    }
    // A 在 B 上方（z 方向）且 x 与 B 重叠的部分
    int xOverlapL = std::max(A.xMin, B.xMin);
    int xOverlapR = std::min(A.xMax, B.xMax);
    if (xOverlapL <= xOverlapR) {
        if (A.zMin < B.zMin) {
            result.push_back({xOverlapL, xOverlapR, A.zMin, B.zMin - 1});
        }
        if (A.zMax > B.zMax) {
            result.push_back({xOverlapL, xOverlapR, B.zMax + 1, A.zMax});
        }
    }
    return result;
}

} // namespace

TerrainScanner& TerrainScanner::getInstance() {
    static TerrainScanner instance;
    return instance;
}

void TerrainScanner::shutdown() { clearState(); }

void TerrainScanner::clearState() {
    scanQueue_.clear();
    scanMap_.clear();
    totalFrames_                 = 0;
    scanRadiusChunks_            = 0;
    lastVisibleCenterChunkPos    = {0, 0, -1};
    lastVisibleScanRadiusChunks_ = -1;
}

std::vector<std::pair<int, int>> TerrainScanner::buildSpiralOffsets(int radiusChunks) {
    std::vector<std::pair<int, int>> offsets;
    offsets.reserve((radiusChunks * 2 + 1) * (radiusChunks * 2 + 1));

    for (int dx = -radiusChunks; dx <= radiusChunks; ++dx) {
        for (int dz = -radiusChunks; dz <= radiusChunks; ++dz) {
            offsets.emplace_back(dx, dz);
        }
    }

    std::stable_sort(offsets.begin(), offsets.end(), [](const auto& a, const auto& b) {
        int da = std::max(std::abs(a.first), std::abs(a.second));
        int db = std::max(std::abs(b.first), std::abs(b.second));
        if (da != db) return da < db;
        int ma = std::abs(a.first) + std::abs(a.second);
        int mb = std::abs(b.first) + std::abs(b.second);
        if (ma != mb) return ma < mb;
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });

    return offsets;
}

void TerrainScanner::updateVisibleSet(const ChunkPosWithDim& playerChunkPos, int scanRadiusChunks) {
    scanRadiusChunks_ = scanRadiusChunks;

    // scanMap_ 为空时，用螺旋顺序初始化扫描队列，保证中心优先扫描
    if (scanMap_.empty() && scanRadiusChunks > 0) {
        for (auto [dx, dz] : buildSpiralOffsets(scanRadiusChunks)) {
            ChunkPosWithDim key{playerChunkPos.x + dx, playerChunkPos.z + dz, playerChunkPos.dimId};
            ScanEntry       entry{totalFrames_, key};
            auto [newIt, inserted] = scanQueue_.insert(entry);
            if (inserted) scanMap_[key] = newIt;
        }
        return;
    }

    ChunkRect oldRect{
        lastVisibleCenterChunkPos.x - lastVisibleScanRadiusChunks_,
        lastVisibleCenterChunkPos.x + lastVisibleScanRadiusChunks_,
        lastVisibleCenterChunkPos.z - lastVisibleScanRadiusChunks_,
        lastVisibleCenterChunkPos.z + lastVisibleScanRadiusChunks_
    };

    ChunkRect newRect{
        playerChunkPos.x - scanRadiusChunks,
        playerChunkPos.x + scanRadiusChunks,
        playerChunkPos.z - scanRadiusChunks,
        playerChunkPos.z + scanRadiusChunks
    };

    // 半径或维度变化：直接全量更新
    if (lastVisibleScanRadiusChunks_ < 0 || playerChunkPos.dimId != lastVisibleCenterChunkPos.dimId) {
        // 移除旧的全部
        scanQueue_.clear();
        scanMap_.clear();
        // 添加新的全部
        // scanMap_ 为空时，用螺旋顺序初始化扫描队列，保证中心优先扫描
        for (auto [dx, dz] : buildSpiralOffsets(scanRadiusChunks)) {
            ChunkPosWithDim key{playerChunkPos.x + dx, playerChunkPos.z + dz, playerChunkPos.dimId};
            ScanEntry       entry{totalFrames_, key};
            auto [newIt, inserted] = scanQueue_.insert(entry);
            if (inserted) scanMap_[key] = newIt;
        }
        return;
    }

    // 中心移动：增量处理
    // 移除离开视野的 chunk
    auto removeRects = subtractRects(oldRect, newRect);
    for (const auto& rect : removeRects) {
        for (int z = rect.zMin; z <= rect.zMax; ++z) {
            for (int x = rect.xMin; x <= rect.xMax; ++x) {
                ChunkPosWithDim key{x, z, playerChunkPos.dimId};
                auto            mapIt = scanMap_.find(key);
                if (mapIt != scanMap_.end()) {
                    scanQueue_.erase(mapIt->second);
                    scanMap_.erase(mapIt);
                }
            }
        }
    }

    // 添加新进入视野的 chunk
    auto addRects = subtractRects(newRect, oldRect);
    for (const auto& rect : addRects) {
        for (int z = rect.zMin; z <= rect.zMax; ++z) {
            for (int x = rect.xMin; x <= rect.xMax; ++x) {
                ChunkPosWithDim key{x, z, playerChunkPos.dimId};
                if (!scanMap_.contains(key)) {
                    ScanEntry entry{totalFrames_, key};
                    auto [newIt, inserted] = scanQueue_.insert(entry);
                    if (inserted) scanMap_[key] = newIt;
                }
            }
        }
    }
}

void TerrainScanner::scanChunk(BlockSource* region, const ChunkPosWithDim& key) const {
    auto        t0    = Clock::now();
    LevelChunk* chunk = region->getChunk(key.x, key.z);
    if (!isChunkLoaded(chunk)) return;

    // 根据维度获取 cameraHeight
    int cameraHeight;
    switch (key.dimId) {
    case 0:
        cameraHeight = config::getConfig().terrain.cameraHeight.overworld;
        break;
    case 1:
        cameraHeight = config::getConfig().terrain.cameraHeight.nether;
        break;
    case 2:
        cameraHeight = config::getConfig().terrain.cameraHeight.end;
        break;
    default:
        cameraHeight = config::getConfig().terrain.cameraHeight.overworld;
        break;
    }

    auto regionData = MapCacheManager::getInstance().getOrCreateRegion(RegionPos(key));
    auto chunkData  = regionData->getOrCreateChunkData(RegionChunkPos(key));

    int minY = region->mMaxHeight;

    bool dataChanged   = false;
    bool heightChanged = false;
    {
        std::unique_lock<std::shared_mutex> lock(chunkData->mutex_);
        for (int chunkWorldPosX = 0; chunkWorldPosX < 16; ++chunkWorldPosX) {
            for (int chunkWorldPosZ = 0; chunkWorldPosZ < 16; ++chunkWorldPosZ) {
                auto color = getTerrainPixelAtCameraHeight(chunk, {chunkWorldPosX, chunkWorldPosZ}, cameraHeight);

                int idx = chunkWorldPosZ * 16 + chunkWorldPosX;

                auto& currentBlockData = chunkData->blockData[chunkWorldPosX][chunkWorldPosZ];

                if (!chunkData->loadChunkBaseData) {

                    chunkData->loadChunkBaseData = true;
                    currentBlockData.color       = color;
                    currentBlockData.height      = static_cast<std::int16_t>(chunk->mHeightmap.get()[idx].mVal + minY);
                    currentBlockData.solidHeight =
                        static_cast<std::int16_t>(chunk->mRenderHeightmap.get()[idx].mVal + minY);

                    dataChanged   = true;
                    heightChanged = true;
                } else {
                    if (currentBlockData.color != color) {
                        currentBlockData.color = color;
                        dataChanged            = true;
                    }
                    if (currentBlockData.height != chunk->mHeightmap.get()[idx].mVal + minY) {
                        currentBlockData.height = static_cast<std::int16_t>(chunk->mHeightmap.get()[idx].mVal + minY);
                        heightChanged           = true;
                    }
                    if (currentBlockData.solidHeight != chunk->mRenderHeightmap.get()[idx].mVal + minY) {
                        currentBlockData.solidHeight =
                            static_cast<std::int16_t>(chunk->mRenderHeightmap.get()[idx].mVal + minY);
                        heightChanged = true;
                    }
                }
            }
        }
        chunkData->lastScanFrame = totalFrames_;
        if (dataChanged) {
            regionData->markDirty();
            regionData->markBakedDirty();
        } else if (heightChanged) regionData->markBakedDirty();
    }

    auto       us         = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - t0).count();
    static int s_chunkLog = 0;
    if ((++s_chunkLog % 60) == 0) {
        MapDemo::getInstance()
            .getSelf()
            .getLogger()
            .debug("TerrainScanner::scanChunk chunk=({},{}), dim={}, time={}us", key.x, key.z, key.dimId, us);
    }
}

// void TerrainScanner::saveChunkToDisk(
//     const ScanChunkKey& key,
//     const RegionData*   data,
//     int                 localChunkX,
//     int                 localChunkZ
// ) {
//     if (!diskCacheEnabled_ || !diskCache_) return;
//     try {
//         auto blob = serializeChunk(data, localChunkX, localChunkZ);
//         diskCache_->set(makeDiskKey(key), blob);
//     } catch (const std::exception& e) {
//         MapDemo::getInstance().getSelf().getLogger().error("TerrainScanner: save chunk to disk failed: {}",
//         e.what());
//     }
// }

// bool TerrainScanner::loadChunkFromDisk(const ScanChunkKey& key, RegionData* data, int localChunkX, int localChunkZ) {
//     if (!diskCacheEnabled_ || !diskCache_) return false;
//     try {
//         auto blob = diskCache_->get(makeDiskKey(key));
//         if (!blob) return false;
//         deserializeChunk(data, localChunkX, localChunkZ, *blob);
//         std::unique_lock<std::shared_mutex> lock(data->mutex_);
//         data->chunkLastScanFrame[localChunkZ * RegionData::CHUNKS + localChunkX] = totalFrames_;
//         return true;
//     } catch (const std::exception& e) {
//         MapDemo::getInstance().getSelf().getLogger().error("TerrainScanner: load chunk from disk failed: {}",
//         e.what()); return false;
//     }
// }

// std::string TerrainScanner::serializeChunk(const RegionData* data, int chunkLocalX, int chunkLocalZ) {
//     std::string blob;
//     blob.reserve(16 * 16 * (4 + 2 + 2 + 1));
//     int startX = chunkLocalX * 16;
//     int startZ = chunkLocalZ * 16;
//     for (int z = 0; z < 16; ++z) {
//         for (int x = 0; x < 16; ++x) {
//             auto c = data->getPixel(startX + x, startZ + z);
//             blob.push_back(static_cast<char>(c.r));
//             blob.push_back(static_cast<char>(c.g));
//             blob.push_back(static_cast<char>(c.b));
//             blob.push_back(static_cast<char>(c.a));
//         }
//     }
//     for (int z = 0; z < 16; ++z) {
//         for (int x = 0; x < 16; ++x) {
//             std::int16_t h = data->getHeight(startX + x, startZ + z);
//             blob.push_back(static_cast<char>(h & 0xFF));
//             blob.push_back(static_cast<char>((h >> 8) & 0xFF));
//         }
//     }
//     for (int z = 0; z < 16; ++z) {
//         for (int x = 0; x < 16; ++x) {
//             std::int16_t h = data->getSolidHeight(startX + x, startZ + z);
//             blob.push_back(static_cast<char>(h & 0xFF));
//             blob.push_back(static_cast<char>((h >> 8) & 0xFF));
//         }
//     }
//     for (int z = 0; z < 16; ++z) {
//         for (int x = 0; x < 16; ++x) {
//             blob.push_back(static_cast<char>(data->getWaterDepth(startX + x, startZ + z)));
//         }
//     }
//     return blob;
// }

// void TerrainScanner::deserializeChunk(RegionData* data, int chunkLocalX, int chunkLocalZ, const std::string& blob) {
//     constexpr size_t expected = 16 * 16 * (4 + 2 + 2 + 1);
//     if (blob.size() < expected) return;
//     int    startX = chunkLocalX * 16;
//     int    startZ = chunkLocalZ * 16;
//     size_t idx    = 0;
//     for (int z = 0; z < 16; ++z) {
//         for (int x = 0; x < 16; ++x) {
//             BlockColor c{
//                 static_cast<std::uint8_t>(blob[idx + 0]),
//                 static_cast<std::uint8_t>(blob[idx + 1]),
//                 static_cast<std::uint8_t>(blob[idx + 2]),
//                 static_cast<std::uint8_t>(blob[idx + 3])
//             };
//             data->setPixel(startX + x, startZ + z, c);
//             idx += 4;
//         }
//     }
//     for (int z = 0; z < 16; ++z) {
//         for (int x = 0; x < 16; ++x) {
//             std::int16_t h = static_cast<std::int16_t>(
//                 static_cast<std::uint8_t>(blob[idx]) | (static_cast<std::uint8_t>(blob[idx + 1]) << 8)
//             );
//             data->setHeight(startX + x, startZ + z, h);
//             idx += 2;
//         }
//     }
//     for (int z = 0; z < 16; ++z) {
//         for (int x = 0; x < 16; ++x) {
//             std::int16_t h = static_cast<std::int16_t>(
//                 static_cast<std::uint8_t>(blob[idx]) | (static_cast<std::uint8_t>(blob[idx + 1]) << 8)
//             );
//             data->setSolidHeight(startX + x, startZ + z, h);
//             idx += 2;
//         }
//     }
//     for (int z = 0; z < 16; ++z) {
//         for (int x = 0; x < 16; ++x) {
//             data->setWaterDepth(startX + x, startZ + z, static_cast<std::uint8_t>(blob[idx]));
//             ++idx;
//         }
//     }
// }

// std::string TerrainScanner::makeDiskKey(const ScanChunkKey& key) {
//     std::string out;
//     out.reserve(32);
//     out.append(reinterpret_cast<const char*>(&key.chunkX), sizeof(key.chunkX));
//     out.append(reinterpret_cast<const char*>(&key.chunkZ), sizeof(key.chunkZ));
//     out.append(reinterpret_cast<const char*>(&key.dim), sizeof(key.dim));
//     return out;
// }

bool TerrainScanner::isChunkLoaded(LevelChunk* chunk) { return chunk && chunk->mLoadState.get() == ChunkState::Loaded; }

void TerrainScanner::update(BlockSource* region, const ChunkPosWithDim& playerChunkPos) {
    ++totalFrames_;
    auto updateT0 = Clock::now();

    auto& cfg              = config::getConfig().terrain;
    int   scanRadiusChunks = cfg.scanRadius / 16;

    // 只有玩家位置、维度或扫描半径变化时才重新构建可见集合
    if (playerChunkPos != lastVisibleCenterChunkPos || scanRadiusChunks != lastVisibleScanRadiusChunks_) {
        updateVisibleSet(playerChunkPos, scanRadiusChunks);
        lastVisibleCenterChunkPos    = playerChunkPos;
        lastVisibleScanRadiusChunks_ = scanRadiusChunks;
    }

    static int s_updateLogCounter = 0;
    bool       shouldLog          = (++s_updateLogCounter % 120 == 0);

    ChunkPosWithDim queueFrontKey{0, 0, 0};
    if (!scanQueue_.empty()) queueFrontKey = scanQueue_.begin()->key;

    if (shouldLog) {
        MapDemo::getInstance().getSelf().getLogger().debug(
            "TerrainScanner::update: frame={}, queue={}, visible={}, playerChunk=({}, {}), dim={}, frontChunk=({}, "
            "{}), frontFrame={}",
            totalFrames_,
            scanQueue_.size(),
            scanMap_.size(),
            playerChunkPos.x,
            playerChunkPos.z,
            playerChunkPos.dimId,
            queueFrontKey.x,
            queueFrontKey.z,
            scanQueue_.empty() ? 0ULL : scanQueue_.begin()->nextScanFrame
        );
    }

    int processed = 0;
    int skipped   = 0;
    int loaded    = 0;
    int evicted   = 0;
    int unloaded  = 0;
    int deferred  = 0;
    while (processed < cfg.scanMaxChunksPerFrame && !scanQueue_.empty()) {
        auto it = scanQueue_.begin();
        if (it->nextScanFrame > totalFrames_) break;

        ChunkPosWithDim key = it->key;
        scanQueue_.erase(it);
        scanMap_.erase(key);

        // // 检查是否仍在视野内
        // int distX    = std::abs(key.chunkX - playerChunkX);
        // int distZ    = std::abs(key.chunkZ - playerChunkZ);
        // int chebDist = std::max(distX, distZ);
        // if (chebDist > scanRadiusChunks * 2) {
        //     // 已离开玩家 2 倍视野半径以上，按 chunk 粒度清除缓存
        //     MapCacheManager::getInstance().evictChunk(key.chunkX, key.chunkZ, key.dim);
        //     ++evicted;
        //     continue;
        // }

        // 检查 chunk 是否已加载
        LevelChunk* chunk = region->getChunk(key.x, key.z);
        if (!isChunkLoaded(chunk)) {
            // 未加载：放到下一轮扫描，不占用本帧处理上限
            ScanEntry newEntry{totalFrames_ + static_cast<std::uint64_t>(cfg.rescanIntervalFrames), key};
            auto [newIt, inserted] = scanQueue_.insert(newEntry);
            if (inserted) {
                scanMap_[key] = newIt;
            }
            ++unloaded;
            continue;
        }
        ++loaded;

        // 检查是否需要扫描：从磁盘加载或检查时间戳
        bool                             needScan = true;
        std::shared_ptr<RegionCacheData> data     = MapCacheManager::getInstance().getOrCreateRegion(RegionPos(key));

        std::uint64_t lastScan = data->getOrCreateChunkData(RegionChunkPos(key))->lastScanFrame;
        if (lastScan && (totalFrames_ - lastScan) < static_cast<std::uint64_t>(cfg.rescanIntervalFrames)) {
            needScan = false;
            ++deferred;
        }

        if (needScan) {
            scanChunk(region, key);
            ++processed;
        }

        // 重新入队，安排下一次扫描
        ScanEntry newEntry{totalFrames_ + static_cast<std::uint64_t>(cfg.rescanIntervalFrames), key};
        auto [newIt, inserted] = scanQueue_.insert(newEntry);
        if (inserted) {
            scanMap_[key] = newIt;
        }
    }

    if (shouldLog) {
        auto totalUs = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - updateT0).count();
        MapDemo::getInstance().getSelf().getLogger().debug(
            "TerrainScanner::update done: processed={}, loaded={}, deferred={}, unloaded={}, skipped={}, evicted={}, "
            "time={}us",
            processed,
            loaded,
            deferred,
            unloaded,
            skipped,
            evicted,
            totalUs
        );
    }

    // 兜底清理：淘汰 scanQueue_ 中离开玩家 2 倍视野半径以上的 chunk（兜底循环暂时保留但改用 scanQueue_）
    // for (auto it = scanQueue_.begin(); it != scanQueue_.end();) {
    //     const auto& key      = it->key;
    //     int         distX    = std::abs(key.chunkX - playerChunkX);
    //     int         distZ    = std::abs(key.chunkZ - playerChunkZ);
    //     int         chebDist = std::max(distX, distZ);
    //     if (chebDist > scanRadiusChunks * 2) {
    //         MapCacheManager::getInstance().evictChunk(key.chunkX, key.chunkZ, key.dim);
    //         scanMap_.erase(key);
    //         it = scanQueue_.erase(it);
    //     } else {
    //         ++it;
    //     }
    // }
}

} // namespace map_demo
