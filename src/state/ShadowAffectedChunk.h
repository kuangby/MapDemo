#pragma once

#include "data/pos/ChunkPosWithDim.h"
#include "data/pos/WorldPos.h"

#include <unordered_set>
#include <vector>

namespace map_demo {

// 计算方块高度变化后阴影可能受影响的 chunk 列表（含自身 chunk）；角度为弧度制
std::vector<ChunkPosWithDim>
getAffectedChunk(int oriHeight, int height, WorldPos pos, float azimuth_rad, float zenith_rad);

// 计算矩形区域（方块坐标，[x0,x1) x [z0,z1)）高度变化后阴影可能受影响的 chunk 列表
// 排除迎光的上游角点，从下游侧其余 3 个角点沿光线方向各发一条射线检测
// higherHeight/lowerHeight 取区域变化后的最高/最低高度
std::vector<ChunkPosWithDim> getAffectedChunksForRect(
    int   x0,
    int   z0,
    int   x1,
    int   z1,
    int   higherHeight,
    int   lowerHeight,
    int   dimId,
    float azimuth_rad,
    float zenith_rad
);

// 将受影响的 chunk 及其 region 标记为 bakedDirty；跳过未加载数据的 chunk
// （未加载的 chunk 首次扫描时会全量 bake，阴影天然正确，无需标脏）
void markAffectedChunksDirty(const std::unordered_set<ChunkPosWithDim>& chunks);

// 柔化级标脏：只重做 PCF 柔化与 bevel（复用已存 shadowOriginData，跳过射线采样）。
// 跳过未加载数据的 chunk；已 full dirty 的 chunk 跳过（full 涵盖 soft）
void markSoftDirty(const ChunkPosWithDim& pos);

// 将 center 的 8 邻接 chunk 标记为 softDirty（邻居的柔化/bevel 依赖本 chunk 的边缘数据）
void markRingSoftDirty(const ChunkPosWithDim& center);

} // namespace map_demo
