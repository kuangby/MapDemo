#pragma once

#include "pos/ChunkWorldPos.h"
#include "state/BlockColorManager.h"

#include <mc/world/level/ChunkBlockPos.h>
#include <mc/world/level/chunk/LevelChunk.h>

#include <string>

namespace map_demo {

// 获取3D生物群系名称（pos 的 y 为基于 minY 的相对高度）
std::string getBiomeName(LevelChunk* chunk, ChunkBlockPos pos);

// 获取 biome fallback 颜色
BlockColor getBiomeFallbackColor(const std::string& biomeName);

// 获取带生物群系混合的方块颜色
BlockColor getBlockColorWithBiome(const std::string& name, const std::string& biomeName);

// 判断方块是否不透明（特判优化）
bool isBlockOpaque(const std::string& name, int dim);

// 处理水的特殊效果（透明水）
BlockColor processWater(LevelChunk* chunk, int cx, int cz, int waterSurfaceY, int minY);

// 单个像素的地形信息
struct TerrainPixelInfo {
    BlockColor color;
    int        surfaceHeight{0}; // mHeightmap
    int        solidHeight{0};   // mRenderHeightmap
    uint8_t    waterDepth{0};
    bool       hasWater{false};
};

// 基于 cameraHeight 的方块颜色获取，同时返回高度信息
BlockColor getTerrainPixelAtCameraHeight(LevelChunk* chunk, ChunkWorldPos pos, int cameraHeight);

} // namespace map_demo
