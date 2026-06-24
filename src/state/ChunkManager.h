#pragma once

#include <vector>

namespace map_demo {

struct ChunkPos {
    int x;
    int z;
};

struct ChunkBounds {
    float minX;
    float minZ;
    float maxX;
    float maxZ;
};

class ChunkManager {
public:
    static constexpr int MINIMAP_RADIUS_CHUNKS = 5; // 5 chunks radius

    static ChunkManager& getInstance();

    /// 根据世界坐标获取所在的 chunk 坐标
    [[nodiscard]] static ChunkPos worldToChunk(float worldX, float worldZ);

    /// 获取以 (centerX, centerZ) 为中心、半径为 radiusChunks 的可见 chunk 列表
    [[nodiscard]] std::vector<ChunkPos> getVisibleChunks(int centerChunkX, int centerChunkZ, int radiusChunks) const;

    /// 获取某个 chunk 的世界坐标边界
    [[nodiscard]] static ChunkBounds getChunkBounds(int chunkX, int chunkZ);

    /// 判断某点是否在某个 chunk 内
    [[nodiscard]] static bool isPointInChunk(float worldX, float worldZ, int chunkX, int chunkZ);
};

} // namespace map_demo
