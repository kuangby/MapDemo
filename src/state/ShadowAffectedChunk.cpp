#include "state/ShadowAffectedChunk.h"

#include "data/cache/MapCacheManager.h"
#include "data/pos/RegionChunkPos.h"
#include "data/pos/RegionPos.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <unordered_set>

namespace map_demo {

namespace {

void traceRay(
    std::vector<ChunkPosWithDim>&        out,
    std::unordered_set<ChunkPosWithDim>& visited,
    WorldPos                             pos,
    int                                  originX,
    int                                  originZ,
    float                                dirX,
    float                                dirZ,
    float                                maxDist,
    int                                  higherHeight,
    int                                  lowerHeight,
    float                                tanZenith
) {
    auto& mapCacheManager = MapCacheManager::getInstance();

    auto curX = static_cast<float>(originX);
    auto curZ = static_cast<float>(originZ);
    // 按方向做 epsilon 偏移计算初始 chunk：原点恰在边界且方向分量为负时，
    // 射线立即进入相邻 chunk，避免 t=0 被钳制后步进卡死
    const float eps = 1e-4f;
    int curChunkX = static_cast<int>(std::floor((curX + (dirX >= 0.0f ? eps : -eps)) / 16.0f));
    int curChunkZ = static_cast<int>(std::floor((curZ + (dirZ >= 0.0f ? eps : -eps)) / 16.0f));

    float dist = 0.0f;

    while (dist < maxDist) {
        ChunkPosWithDim chunk{curChunkX, curChunkZ, pos.dimId};

        if (!visited.contains(chunk)) {
            visited.emplace(chunk);

            int chunkMinX = curChunkX * 16;
            int chunkMaxX = curChunkX * 16 + 16;
            int chunkMinZ = curChunkZ * 16;
            int chunkMaxZ = curChunkZ * 16 + 16;

            // 射线起点到该 chunk 的最近点
            int  closestX    = std::clamp(originX, chunkMinX, chunkMaxX);
            int  closestZ    = std::clamp(originZ, chunkMinZ, chunkMaxZ);
            auto minDistance = static_cast<float>(
                std::sqrt((closestX - originX) * (closestX - originX) + (closestZ - originZ) * (closestZ - originZ))
            );

            // 射线起点到该 chunk 的最远角
            int  farX = std::abs(originX - chunkMinX) > std::abs(originX - chunkMaxX) ? chunkMinX : chunkMaxX;
            int  farZ = std::abs(originZ - chunkMinZ) > std::abs(originZ - chunkMaxZ) ? chunkMinZ : chunkMaxZ;
            auto maxDistance =
                static_cast<float>(std::sqrt((farX - originX) * (farX - originX) + (farZ - originZ) * (farZ - originZ))
                );

            auto chunkData = mapCacheManager.getChunk(chunk);
            // 未扫描的 chunk 高度统计无效（min/max 为默认值），不参与裁剪；
            // 其首次扫描时会全量 bake，阴影天然正确，无需标脏
            if (chunkData && chunkData->loadChunkBaseData) {
                // 1. 较高高度在最小距离处都够不着该 chunk 最低点
                //    => 该 chunk 在新旧状态下都不在阴影中
                if (static_cast<float>(higherHeight) - minDistance * tanZenith
                    < static_cast<float>(chunkData->minHeight)) {
                    break;
                }

                // 2. 较低高度在最大距离处仍能覆盖该 chunk 最高点
                //    => 该 chunk 在新旧状态下都被完全阴影覆盖，状态无变化
                if (static_cast<float>(lowerHeight) - maxDistance * tanZenith
                    >= static_cast<float>(chunkData->maxHeight)) {
                    continue;
                }
                out.emplace_back(chunk);
            }
        }

        // 计算下一个 chunk 边界
        int nextX = (dirX >= 0.0f) ? (curChunkX + 1) * 16 : curChunkX * 16;
        int nextZ = (dirZ >= 0.0f) ? (curChunkZ + 1) * 16 : curChunkZ * 16;

        float tX = (dirX != 0.0f) ? (static_cast<float>(nextX) - curX) / dirX : std::numeric_limits<float>::max();
        float tZ = (dirZ != 0.0f) ? (static_cast<float>(nextZ) - curZ) / dirZ : std::numeric_limits<float>::max();

        if (tX <= 1e-5f) tX = std::numeric_limits<float>::max();
        if (tZ <= 1e-5f) tZ = std::numeric_limits<float>::max();

        float stepDist = std::min(tX, tZ);

        if (dist + stepDist > maxDist) break;

        curX += dirX * stepDist;
        curZ += dirZ * stepDist;
        dist += stepDist;

        // 由实际坐标重算所在 chunk（沿用 epsilon 偏移），保证跨越边界后 chunk 坐标一致
        curChunkX = static_cast<int>(std::floor((curX + (dirX >= 0.0f ? eps : -eps)) / 16.0f));
        curChunkZ = static_cast<int>(std::floor((curZ + (dirZ >= 0.0f ? eps : -eps)) / 16.0f));
    }
}

} // namespace

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
) {
    float tanZenith = std::tan(zenith_rad);

    std::vector<ChunkPosWithDim>        res;
    std::unordered_set<ChunkPosWithDim> visited;
    res.reserve(7);
    visited.reserve(10);

    // 矩形覆盖的 chunk 先加入结果
    auto minChunk = ChunkPosWithDim{
        WorldPos{x0, z0, dimId}
    };
    auto maxChunk = ChunkPosWithDim{
        WorldPos{x1 - 1, z1 - 1, dimId}
    };
    for (int cz = minChunk.z; cz <= maxChunk.z; ++cz) {
        for (int cx = minChunk.x; cx <= maxChunk.x; ++cx) {
            res.emplace_back(cx, cz, dimId);
            visited.emplace(cx, cz, dimId);
        }
    }

    // 下游方向
    float dirX = -std::sin(azimuth_rad);
    float dirZ = std::cos(azimuth_rad);
    if (std::abs(dirX) < 1e-5f) dirX = 0.0f;
    if (std::abs(dirZ) < 1e-5f) dirZ = 0.0f;

    // 角点与下游方向做点积，值最大者为下游（光线方向）角点；
    // 方向与区块线平行时下游为整条边（2 个角点并列），一并排除
    const std::pair<int, int> corners[4] = {
        {x0, z0},
        {x1, z0},
        {x0, z1},
        {x1, z1}
    };
    float maxDot = std::numeric_limits<float>::lowest();
    for (auto& [cx, cz] : corners) {
        float dot = static_cast<float>(cx) * dirX + static_cast<float>(cz) * dirZ;
        if (dot > maxDot) maxDot = dot;
    }

    WorldPos pos{x0, z0, dimId}; // traceRay 仅使用其 dimId
    float    maxDist = 96.0f;

    std::pair<int, int> downstreamCorners[2];
    int                 downstreamCount = 0;
    std::pair<int, int> tracedOrigins[2];
    int                 tracedCount = 0;
    for (auto& [cx, cz] : corners) {
        float dot = static_cast<float>(cx) * dirX + static_cast<float>(cz) * dirZ;
        if (dot >= maxDot - 1e-4f) {
            // 下游角点夹取到矩形内，供终点 chunk 判定使用
            downstreamCorners[downstreamCount++] = {
                std::clamp(cx, x0, x1 - 1),
                std::clamp(cz, z0, z1 - 1)
            };
            continue;
        }
        // 非下游角点作为射线原点；排他边界角点夹取到矩形内，重复原点只追踪一次
        int ox = std::clamp(cx, x0, x1 - 1);
        int oz = std::clamp(cz, z0, z1 - 1);
        bool dup = false;
        for (int i = 0; i < tracedCount; ++i) {
            if (tracedOrigins[i].first == ox && tracedOrigins[i].second == oz) {
                dup = true;
                break;
            }
        }
        if (dup) continue;
        tracedOrigins[tracedCount++] = {ox, oz};
        traceRay(res, visited, pos, ox, oz, dirX, dirZ, maxDist, higherHeight, lowerHeight, tanZenith);
    }

    // 阴影终点方块（扫掠区域最前角点）所在 chunk 可能不被任何一条射线覆盖，单独判定
    for (int i = 0; i < downstreamCount; ++i) {
        int endX = static_cast<int>(
            std::floor(static_cast<float>(downstreamCorners[i].first) + maxDist * dirX)
        );
        int endZ = static_cast<int>(
            std::floor(static_cast<float>(downstreamCorners[i].second) + maxDist * dirZ)
        );

        auto farChunk = ChunkPosWithDim{
            WorldPos{endX, endZ, dimId}
        };
        if (!visited.emplace(farChunk).second) continue;

        int chunkMinX = farChunk.x * 16;
        int chunkMaxX = farChunk.x * 16 + 16;
        int chunkMinZ = farChunk.z * 16;
        int chunkMaxZ = farChunk.z * 16 + 16;

        // 终点方块到该 chunk 的最近点；阴影高度按距射线原点（下游角点）计算，需加上 maxDist
        int   closestX    = std::clamp(endX, chunkMinX, chunkMaxX);
        int   closestZ    = std::clamp(endZ, chunkMinZ, chunkMaxZ);
        float minDistance = maxDist
                          + static_cast<float>(std::sqrt(
                                (closestX - endX) * (closestX - endX) + (closestZ - endZ) * (closestZ - endZ)
                            ));

        // 终点方块到该 chunk 的最远角
        int   farX        = std::abs(endX - chunkMinX) > std::abs(endX - chunkMaxX) ? chunkMinX : chunkMaxX;
        int   farZ        = std::abs(endZ - chunkMinZ) > std::abs(endZ - chunkMaxZ) ? chunkMinZ : chunkMaxZ;
        float maxDistance = maxDist
                          + static_cast<float>(
                                std::sqrt((farX - endX) * (farX - endX) + (farZ - endZ) * (farZ - endZ))
                            );

        auto chunkData = MapCacheManager::getInstance().getChunk(farChunk);
        bool affected  = chunkData && chunkData->loadChunkBaseData
                    && static_cast<float>(higherHeight) - minDistance * tanZenith
                           > static_cast<float>(chunkData->minHeight)
                    && static_cast<float>(lowerHeight) - maxDistance * tanZenith
                           < static_cast<float>(chunkData->maxHeight);
        if (affected) {
            res.emplace_back(farChunk);
        }
    }

    return res;
}

std::vector<ChunkPosWithDim>
getAffectedChunk(int oriHeight, int height, WorldPos pos, float azimuth_rad, float zenith_rad) {
    return getAffectedChunksForRect(
        pos.x,
        pos.z,
        pos.x + 1,
        pos.z + 1,
        std::max(oriHeight, height),
        std::min(oriHeight, height),
        pos.dimId,
        azimuth_rad,
        zenith_rad
    );
}

void markAffectedChunksDirty(const std::unordered_set<ChunkPosWithDim>& chunks) {
    auto& mapCacheManager = MapCacheManager::getInstance();
    for (auto& pos : chunks) {
        auto region = mapCacheManager.getRegion(RegionPos(pos));
        if (!region) {
            continue;
        }
        auto chunk = region->getChunkData(RegionChunkPos(pos));
        // 跳过未加载数据的 chunk：首次扫描时会全量 bake，无需标脏
        if (!chunk || !chunk->loadChunkBaseData) {
            continue;
        }
        chunk->markBakedDirty();
        region->markBakedDirty();
    }
}

void markSoftDirty(const ChunkPosWithDim& pos) {
    auto& mapCacheManager = MapCacheManager::getInstance();
    auto  region          = mapCacheManager.getRegion(RegionPos(pos));
    if (!region) return;
    auto chunk = region->getChunkData(RegionChunkPos(pos));
    // 未加载数据的 chunk 首扫时会全量 bake；full dirty 已涵盖 soft
    if (!chunk || !chunk->loadChunkBaseData || chunk->isBakedDirty()) return;
    chunk->markBakedSoftDirty();
    region->markBakedDirty();
}

void markRingSoftDirty(const ChunkPosWithDim& center) {
    for (int dz = -1; dz <= 1; ++dz) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (!dx && !dz) continue;
            markSoftDirty(ChunkPosWithDim{center.x + dx, center.z + dz, center.dimId});
        }
    }
}

} // namespace map_demo
