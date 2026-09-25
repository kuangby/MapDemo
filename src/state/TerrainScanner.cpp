#include "state/TerrainScanner.h"

#include "config/Config.h"
#include "data/cache/MapCacheManager.h"
#include "data/pos/ChunkPosWithDim.h"
#include "data/pos/ChunkWorldPos.h"
#include "data/pos/RegionChunkPos.h"
#include "data/pos/RegionPos.h"
#include "state/ShadowAffectedChunk.h"
#include "state/TerrainColorUtils.h"


#include "mc/world/level/chunk/ChunkSource.h"
#include "mc/world/level/chunk/SubChunk.h"
#include "mc/world/level/dimension/Dimension.h"
#include <mc/world/level/BlockSource.h>
#include <mc/world/level/ChunkBlockPos.h>
#include <mc/world/level/ChunkLocalHeight.h>
#include <mc/world/level/biome/Biome.h>
#include <mc/world/level/block/Block.h>


#include <algorithm>
#include <cmath>
#include <limits>
#include <unordered_set>

namespace map_demo {

namespace {

// 未加载 chunk 的重试间隔（帧），远小于 rescanIntervalFrames，保证 chunk 加载后很快被扫描
constexpr std::uint64_t kUnloadedRetryFrames = 20;

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

bool TerrainScanner::scanChunk(BlockSource* region, const ChunkPosWithDim& key, bool& outHitPlaceholder) const {
    auto chunk = region->getChunk(key.x, key.z);
    if (!isChunkLoaded(chunk)) return false;

    outHitPlaceholder = false;

    // 子区块预检：任何一个子区块仍是占位符（服务器数据未到达）就放弃整个 chunk，
    // 由调用方按短延迟重新入队，避免扫出半黑半真的混合数据
    for (const auto& subChunk : chunk->mSubChunks.get()) {
        if (subChunk.isPlaceHolderSubChunk()) {
            outHitPlaceholder = true;
            return false;
        }
    }

    // 扫描相机高度（Y 坐标）：主世界 320，地狱 127（基岩层顶），末地 256
    int cameraHeight;
    switch (key.dimId) {
    case 1:  cameraHeight = 127; break;
    case 2:  cameraHeight = 256; break;
    default: cameraHeight = 320; break;
    }

    auto regionData = MapCacheManager::getInstance().getOrCreateRegion(RegionPos(key));
    auto chunkData  = regionData->getOrCreateChunkData(RegionChunkPos(key));

    int minY = region->mMinHeight;

    bool changed       = false;
    bool heightChanged = false;

    int chunkMinHeight = std::numeric_limits<int>::max();
    int chunkMaxHeight = std::numeric_limits<int>::min();
    int oldMinHeight   = 0;
    int oldMaxHeight   = 0;

    {
        std::unique_lock<std::shared_mutex> lock(chunkData->mutex_);
        oldMinHeight = chunkData->minHeight;
        oldMaxHeight = chunkData->maxHeight;
        for (int chunkWorldPosZ = 0; chunkWorldPosZ < 16; ++chunkWorldPosZ) {
            for (int chunkWorldPosX = 0; chunkWorldPosX < 16; ++chunkWorldPosX) {
                auto color = getTerrainPixelAtCameraHeight(
                    chunk,
                    {chunkWorldPosX, chunkWorldPosZ},
                    cameraHeight,
                    outHitPlaceholder
                );

                int idx = chunkWorldPosZ * 16 + chunkWorldPosX;

                int heightVal = chunk->mHeightmap.get()[idx].mVal + minY;
                if (heightVal < chunkMinHeight) chunkMinHeight = heightVal;
                if (heightVal > chunkMaxHeight) chunkMaxHeight = heightVal;

                auto& currentBlockData = chunkData->blocksData[chunkWorldPosZ][chunkWorldPosX];

                if (!chunkData->loadChunkBaseData) {

                    chunkData->loadChunkBaseData = true;
                    currentBlockData.color       = color;
                    currentBlockData.height      = static_cast<std::int16_t>(heightVal);
                    currentBlockData.solidHeight =
                        static_cast<std::int16_t>(chunk->mRenderHeightmap.get()[idx].mVal + minY);

                    changed = true;
                } else {
                    if (currentBlockData.color != color) {
                        currentBlockData.color = color;
                        changed                = true;
                    }
                    if (currentBlockData.height != heightVal) {
                        currentBlockData.height = static_cast<std::int16_t>(heightVal);
                        changed                 = true;
                        heightChanged           = true;
                    }
                    if (currentBlockData.solidHeight != chunk->mRenderHeightmap.get()[idx].mVal + minY) {
                        currentBlockData.solidHeight =
                            static_cast<std::int16_t>(chunk->mRenderHeightmap.get()[idx].mVal + minY);
                        changed = true;
                    }
                }
            }
        }
        chunkData->minHeight = chunkMinHeight;
        chunkData->maxHeight = chunkMaxHeight;
        // 命中占位符时不更新 lastScanFrame，保证短延迟重试不被 needScan 检查跳过
        if (!outHitPlaceholder) {
            chunkData->lastScanFrame = totalFrames_;
        }
    }
    if (changed) {
        chunkData->markBakedDirty();
        regionData->markBakedDirty();
    }

    // 高度变化会影响下游 chunk 的阴影：以整个 chunk 为单位计算受影响 chunk 并标脏
    if (heightChanged) {
        const float deg2rad     = 3.1415926535f / 180.0f;
        auto&       shadowCfg   = config::getConfig().terrain.shadow;
        float       azimuth_rad = shadowCfg.lightAzimuth * deg2rad;
        float       zenith_rad  = shadowCfg.lightZenith * deg2rad;

        auto affected = getAffectedChunksForRect(
            key.x * 16,
            key.z * 16,
            key.x * 16 + 16,
            key.z * 16 + 16,
            std::max(oldMaxHeight, chunkMaxHeight),
            std::min(oldMinHeight, chunkMinHeight),
            key.dimId,
            azimuth_rad,
            zenith_rad
        );
        markAffectedChunksDirty(std::unordered_set<ChunkPosWithDim>(affected.begin(), affected.end()));
    }

    return true;
}

bool TerrainScanner::scanColumn(
    BlockSource*           region,
    const ChunkPosWithDim& key,
    ChunkWorldPos          pos,
    bool&                  outHitPlaceholder
) const {
    auto chunk = region->getChunk(key.x, key.z);
    if (!isChunkLoaded(chunk)) return false;

    outHitPlaceholder = false;

    // 扫描相机高度（Y 坐标）：主世界 320，地狱 127（基岩层顶），末地 256
    int cameraHeight;
    switch (key.dimId) {
    case 1:  cameraHeight = 127; break;
    case 2:  cameraHeight = 256; break;
    default: cameraHeight = 320; break;
    }

    auto regionData = MapCacheManager::getInstance().getOrCreateRegion(RegionPos(key));
    auto chunkData  = regionData->getOrCreateChunkData(RegionChunkPos(key));

    int minY      = region->mMinHeight;
    int idx       = pos.z * 16 + pos.x;
    int heightVal = chunk->mHeightmap.get()[idx].mVal + minY;
    int solidVal  = chunk->mRenderHeightmap.get()[idx].mVal + minY;

    bool changed       = false;
    bool heightChanged = false;
    int  oldHeight     = 0;

    {
        std::unique_lock<std::shared_mutex> lock(chunkData->mutex_);

        // 基础数据尚未整体扫描过：单列更新无意义，交给整 chunk 扫描
        if (!chunkData->loadChunkBaseData) return false;

        auto color = getTerrainPixelAtCameraHeight(chunk, pos, cameraHeight, outHitPlaceholder);

        auto& currentBlockData = chunkData->blocksData[pos.z][pos.x];
        oldHeight              = currentBlockData.height;

        if (currentBlockData.color != color) {
            currentBlockData.color = color;
            changed                = true;
        }
        if (currentBlockData.height != heightVal) {
            currentBlockData.height = static_cast<std::int16_t>(heightVal);
            changed                 = true;
            heightChanged           = true;
        }
        if (currentBlockData.solidHeight != solidVal) {
            currentBlockData.solidHeight = static_cast<std::int16_t>(solidVal);
            changed                      = true;
        }
        // 高度范围只扩不缩：收缩需要整扫（周期重扫会修正），
        // 偏大的范围只会让阴影剔除更保守，不会错剔除
        if (heightVal < chunkData->minHeight) chunkData->minHeight = heightVal;
        if (heightVal > chunkData->maxHeight) chunkData->maxHeight = heightVal;
    }

    if (changed) {
        chunkData->markBakedDirty();
        regionData->markBakedDirty();
    }

    // 该列高度变化会影响下游阴影：以单列范围计算受影响 chunk 并标脏
    if (heightChanged) {
        const float deg2rad   = 3.1415926535f / 180.0f;
        auto&       shadowCfg = config::getConfig().terrain.shadow;
        auto        affected  = getAffectedChunk(
            oldHeight,
            heightVal,
            WorldPos(key.x * 16 + pos.x, key.z * 16 + pos.z, key.dimId),
            shadowCfg.lightAzimuth * deg2rad,
            shadowCfg.lightZenith * deg2rad
        );
        markAffectedChunksDirty(std::unordered_set<ChunkPosWithDim>(affected.begin(), affected.end()));
    }

    return true;
}

bool TerrainScanner::isChunkLoaded(LevelChunk* chunk) { return chunk && chunk->mLoadState.get() == ChunkState::Loaded; }

void TerrainScanner::update(BlockSource* region, const ChunkPosWithDim& playerChunkPos) {
    ++totalFrames_;

    auto& cfg              = config::getConfig().terrain;
    int   scanRadiusChunks = cfg.scanRadius / 16;

    // 只有玩家位置、维度或扫描半径变化时才重新构建可见集合
    if (playerChunkPos != lastVisibleCenterChunkPos || scanRadiusChunks != lastVisibleScanRadiusChunks_) {
        updateVisibleSet(playerChunkPos, scanRadiusChunks);
        lastVisibleCenterChunkPos    = playerChunkPos;
        lastVisibleScanRadiusChunks_ = scanRadiusChunks;
    }

    int processed = 0;
    while (processed < cfg.scanMaxChunksPerFrame && !scanQueue_.empty()) {
        auto it = scanQueue_.begin();
        if (it->nextScanFrame > totalFrames_) break;

        ChunkPosWithDim key = it->key;
        scanQueue_.erase(it);
        scanMap_.erase(key);

        // 检查 chunk 是否已加载
        LevelChunk* chunk = region->getChunk(key.x, key.z);
        if (!isChunkLoaded(chunk)) {
            // 未加载：短延迟后重试，不占用本帧处理上限
            ScanEntry newEntry{totalFrames_ + kUnloadedRetryFrames, key};
            auto [newIt, inserted] = scanQueue_.insert(newEntry);
            if (inserted) {
                scanMap_[key] = newIt;
            }
            continue;
        }

        // 检查是否需要扫描：从磁盘加载或检查时间戳
        bool                             needScan = true;
        std::shared_ptr<RegionCacheData> data     = MapCacheManager::getInstance().getOrCreateRegion(RegionPos(key));

        std::uint64_t lastScan = data->getOrCreateChunkData(RegionChunkPos(key))->lastScanFrame;
        if (lastScan && (totalFrames_ - lastScan) < static_cast<std::uint64_t>(cfg.rescanIntervalFrames)) {
            needScan = false;
        }

        if (needScan) {
            bool hitPlaceholder = false;
            if (scanChunk(region, key, hitPlaceholder)) {
                ++processed;
                // 扫描成功：命中占位符的按短延迟重扫，否则按正常重扫间隔
                std::uint64_t interval =
                    hitPlaceholder ? kUnloadedRetryFrames : static_cast<std::uint64_t>(cfg.rescanIntervalFrames);
                ScanEntry newEntry{totalFrames_ + interval, key};
                auto [newIt, inserted] = scanQueue_.insert(newEntry);
                if (inserted) {
                    scanMap_[key] = newIt;
                }
            } else {
                // 扫描失败：短延迟后重试
                ScanEntry newEntry{totalFrames_ + kUnloadedRetryFrames, key};
                auto [newIt, inserted] = scanQueue_.insert(newEntry);
                if (inserted) {
                    scanMap_[key] = newIt;
                }
            }
            continue;
        }

        // 重新入队，安排下一次扫描
        ScanEntry newEntry{totalFrames_ + static_cast<std::uint64_t>(cfg.rescanIntervalFrames), key};
        auto [newIt, inserted] = scanQueue_.insert(newEntry);
        if (inserted) {
            scanMap_[key] = newIt;
        }
    }
}

} // namespace map_demo
