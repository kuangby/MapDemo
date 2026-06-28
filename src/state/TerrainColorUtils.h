#pragma once

#include "state/BlockColorManager.h"

#include <mc/world/level/chunk/LevelChunk.h>

#include <functional>
#include <string>

namespace map_demo {

// 获取3D生物群系名称
std::string getBiomeNameAtY(LevelChunk* chunk, int cx, int cz, int y, int minY);

// 获取 biome fallback 颜色
BlockColor getBiomeFallbackColor(const std::string& biomeName);

// 获取带生物群系混合的方块颜色
BlockColor getBlockColorWithBiome(const std::string& name, const std::string& biomeName);

// 判断方块是否不透明（特判优化）
bool isBlockOpaque(const std::string& name, int dim);

// 处理水的特殊效果（透明水）
BlockColor processWater(
    LevelChunk* chunk,
    int         cx,
    int         cz,
    int         waterSurfaceY,
    int         minY,
    const std::string& /*biomeName*/,
    const std::function<BlockColor(const std::string&, int)>& getBlockColorWithBiome
);

// 基于 cameraHeight 的方块颜色获取
BlockColor getBlockColorAtCameraHeight(
    LevelChunk* chunk, int cx, int cz, int cameraHeight, int minY, int maxY, int dim
);

} // namespace map_demo
