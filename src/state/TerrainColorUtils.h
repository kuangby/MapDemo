#pragma once

#include "data/BlockColor.h"
#include "data/pos/ChunkWorldPos.h"


#include <mc/world/level/ChunkBlockPos.h>
#include <mc/world/level/chunk/LevelChunk.h>

class BlockSource;

namespace coral_map {

// 透明水拆分结果：固体色与水面信息分开，水面在烘焙期阴影之后叠加
struct WaterSplit {
    BlockColor solidColor;                  // 水下固体色（找不到固体时回退水面色）
    BlockColor waterSurfaceColor{0, 0, 0, 0}; // 水面颜色（已群系混合）
    uint8_t    waterDepth{0};               // 0 = 无水
};

// 处理水的特殊效果（透明水）；水下查找遇到占位符方块时置 outHitPlaceholder 触发快速回扫
WaterSplit
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
// outWater：非空且命中透明水时填充分离出的水面信息（此时返回值是水下固体色）
BlockColor getTerrainPixelAtCameraHeight(
    LevelChunk*   chunk,
    ChunkWorldPos pos,
    int           cameraHeight,
    bool&         outHitPlaceholder,
    WaterSplit*   outWater = nullptr
);

} // namespace coral_map
