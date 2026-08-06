#pragma once

#include "config/Config.h"
#include "data/cache/MapCacheManager.h"
#include "data/pos/ChunkPosWithDim.h"
#include "data/pos/ChunkWorldPos.h"
#include "data/pos/RegionChunkPos.h"
#include "data/pos/RegionPos.h"
#include "data/pos/WorldPos.h"
#include "state/TerrainScanner.h"
#include "state/render/RegionShadowRenderer.h"

#include "mc/world/level/BlockSource.h"
#include "mc/world/level/BlockSourceListener.h"
#include "mc/world/level/block/Block.h"

#include <cmath>
#include <unordered_set>


namespace map_demo {
class BlockChangeListener : public BlockSourceListener {
public:
    void onBlockChanged(
        ::BlockSource&    source,
        ::BlockPos const& pos,
        uint /*layer*/,
        ::Block const& block,
        ::Block const& oldBlock,
        int /*updateFlags*/,
        ::ActorBlockSyncMessage const* /*syncMsg*/,
        ::BlockChangedEventTarget /*eventTarget*/,
        ::Actor* /*blockChangeSource*/
    ) override {
        if (block.getTypeName() == oldBlock.getTypeName()) return;

        auto& mapCacheManager = MapCacheManager::getInstance();

        WorldPos worldPos{pos.x, pos.z, static_cast<int>(source.getDimensionId())};

        auto region = mapCacheManager.getRegion(RegionPos(worldPos));
        if (!region || !region->hasEverBaked()) return;

        auto chunkPos = ChunkPosWithDim(worldPos);
        auto chunk    = mapCacheManager.getChunk(chunkPos);

        bool hasOriHeight = chunk && chunk->loadChunkBaseData;
        int  oriHeight    = 0;
        if (hasOriHeight) oriHeight = chunk->getHeight(ChunkWorldPos(worldPos));

        TerrainScanner::getInstance().scanChunk(&source, chunkPos);

        if (!hasOriHeight) return;

        chunk = mapCacheManager.getChunk(chunkPos);
        if (!chunk) return;
        int newHeight = chunk->getHeight(ChunkWorldPos(worldPos));
        if (newHeight == oriHeight) return;

        const float deg2rad  = 3.1415926535f / 180.0f;
        auto&       shadow   = config::getConfig().terrain.shadow;
        auto        affected = getAffectedChunk(
            oriHeight,
            newHeight,
            worldPos,
            shadow.lightAzimuth * deg2rad,
            shadow.lightZenith * deg2rad
        );
        for (auto& affectedPos : affected) {
            pendingChunks_.insert(affectedPos);
        }
    }

    // tick 末统一处理本 tick 收集到的受影响 chunk
    static void drainPendingChunks() {
        if (pendingChunks_.empty()) return;
        auto& mapCacheManager = MapCacheManager::getInstance();
        for (auto& chunkPos : pendingChunks_) {
            auto region = mapCacheManager.getRegion(RegionPos(chunkPos));
            if (!region || !region->hasEverBaked()) continue;
            auto chunk = region->getChunkData(RegionChunkPos(chunkPos));
            if (chunk) chunk->markBakedDirty();
            region->markBakedDirty();
        }
        pendingChunks_.clear();
    }

    static void clearPendingChunks() { pendingChunks_.clear(); }

public:
    [[nodiscard]] static BlockChangeListener& getInstance() {
        static BlockChangeListener instance;
        return instance;
    }

private:
    inline static std::unordered_set<ChunkPosWithDim> pendingChunks_{};
};
} // namespace map_demo
