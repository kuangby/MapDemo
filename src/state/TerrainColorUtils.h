#pragma once

#include "data/BlockColor.h"
#include "data/pos/ChunkWorldPos.h"


#include <mc/world/level/ChunkBlockPos.h>
#include <mc/world/level/chunk/LevelChunk.h>

class BlockSource;

namespace map_demo {

// 处理水的特殊效果（透明水）；水下查找遇到占位符方块时置 outHitPlaceholder 触发快速回扫
BlockColor
processWater(LevelChunk* chunk, BlockSource& source, int cx, int cz, int waterSurfaceY, int minY, bool& outHitPlaceholder);

// 单个像素的地形信息
struct TerrainPixelInfo {
    BlockColor color;
    int        surfaceHeight{0}; // mHeightmap
    int        solidHeight{0};   // mRenderHeightmap
    uint8_t    waterDepth{0};
    bool       hasWater{false};
};

// 基于 cameraHeight 的方块颜色获取，同时返回高度信息
// outHitPlaceholder：走查过程中遇到 client_request_placeholder_block 时置 true
BlockColor getTerrainPixelAtCameraHeight(LevelChunk* chunk, ChunkWorldPos pos, int cameraHeight, bool& outHitPlaceholder);

} // namespace map_demo
