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


namespace coral_map {
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

        // 只重扫变化的这一列；chunk 基础数据未初始化或命中占位符时回退整 chunk 扫描
        bool hitPlaceholder = false;
        if (!TerrainScanner::getInstance().scanColumn(&source, chunkPos, ChunkWorldPos(worldPos), hitPlaceholder)
            || hitPlaceholder) {
            bool unused;
            TerrainScanner::getInstance().scanChunk(&source, chunkPos, unused);
        }

        // TerrainScanner::getInstance().scanChunk(&source, chunkPos, hitPlaceholder);
    }

public:
    [[nodiscard]] static BlockChangeListener& getInstance() {
        static BlockChangeListener instance;
        return instance;
    }
};
} // namespace coral_map
