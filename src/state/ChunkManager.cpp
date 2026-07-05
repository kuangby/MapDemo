#include "state/ChunkManager.h"

namespace map_demo {

ChunkManager& ChunkManager::getInstance() {
    static ChunkManager instance;
    return instance;
}

std::vector<ChunkPos> ChunkManager::getVisibleChunks(int centerChunkX, int centerChunkZ, int radiusChunks) const {
    std::vector<ChunkPos> result;
    result.reserve(static_cast<size_t>((radiusChunks * 2 + 1) * (radiusChunks * 2 + 1)));

    for (int dx = -radiusChunks; dx <= radiusChunks; ++dx) {
        for (int dz = -radiusChunks; dz <= radiusChunks; ++dz) {
            result.push_back({centerChunkX + dx, centerChunkZ + dz});
        }
    }
    return result;
}

ChunkBounds ChunkManager::getChunkBounds(int chunkX, int chunkZ) {
    return {
        static_cast<float>(chunkX * 16),
        static_cast<float>(chunkZ * 16),
        static_cast<float>((chunkX + 1) * 16),
        static_cast<float>((chunkZ + 1) * 16)
    };
}

ChunkManager::GridLines ChunkManager::getGridLines(int centerChunkX, int centerChunkZ, int radiusChunks) {
    GridLines result;
    int       minX = centerChunkX - radiusChunks;
    int       maxX = centerChunkX + radiusChunks;
    int       minZ = centerChunkZ - radiusChunks;
    int       maxZ = centerChunkZ + radiusChunks;

    // 横线：沿 x 方向，z = minZ .. maxZ+1
    for (int z = minZ; z <= maxZ + 1; ++z) {
        result.horizontal.push_back({
            static_cast<float>(z * 16),
            {static_cast<float>(minX * 16), static_cast<float>((maxX + 1) * 16)}
        });
    }

    // 竖线：沿 z 方向，x = minX .. maxX+1
    for (int x = minX; x <= maxX + 1; ++x) {
        result.vertical.push_back({
            static_cast<float>(x * 16),
            {static_cast<float>(minZ * 16), static_cast<float>((maxZ + 1) * 16)}
        });
    }

    return result;
}

bool ChunkManager::isPointInChunk(float worldX, float worldZ, int chunkX, int chunkZ) {
    auto bounds = getChunkBounds(chunkX, chunkZ);
    return worldX >= bounds.minX && worldX < bounds.maxX && worldZ >= bounds.minZ && worldZ < bounds.maxZ;
}

} // namespace map_demo
