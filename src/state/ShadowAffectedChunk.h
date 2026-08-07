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
// 根据光线方向选取非下游角点作为射线原点（对角方向 3 个，与区块线平行时 2 个）
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

} // namespace map_demo
