#include "state/ChunkManager.h"

#include <cmath>

namespace map_demo {

ChunkManager& ChunkManager::getInstance() {
    static ChunkManager instance;
    return instance;
}

ChunkPos ChunkManager::worldToChunk(float worldX, float worldZ) {
    return {static_cast<int>(std::floor(worldX)) >> 4, static_cast<int>(std::floor(worldZ)) >> 4};
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

bool ChunkManager::isPointInChunk(float worldX, float worldZ, int chunkX, int chunkZ) {
    auto bounds = getChunkBounds(chunkX, chunkZ);
    return worldX >= bounds.minX && worldX < bounds.maxX && worldZ >= bounds.minZ && worldZ < bounds.maxZ;
}

} // namespace map_demo
