#pragma once

#include <vector>


namespace map_demo {

struct ChunkBounds {
    float minX;
    float minZ;
    float maxX;
    float maxZ;
};

class ChunkManager {
public:
    static ChunkManager& getInstance();

    /// 获取某个 chunk 的世界坐标边界
    [[nodiscard]] static ChunkBounds getChunkBounds(int chunkX, int chunkZ);

    /// 计算绘制网格所需的横线和竖线端点集合，避免重复绘制公共边
    struct GridLines {
        std::vector<std::pair<float, std::pair<float, float>>> horizontal; // z, (x1, x2)
        std::vector<std::pair<float, std::pair<float, float>>> vertical;   // x, (z1, z2)
    };
    [[nodiscard]] static GridLines getGridLines(int centerChunkX, int centerChunkZ, int radiusChunks);

    /// 判断某点是否在某个 chunk 内
    [[nodiscard]] static bool isPointInChunk(float worldX, float worldZ, int chunkX, int chunkZ);
};

} // namespace map_demo
