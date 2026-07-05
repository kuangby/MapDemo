#pragma once

#include "ChunkPosWithDim.h"
#include "WorldPos.h"


namespace map_demo {
class RegionChunkPos {
public:
    int x;
    int z;

    [[nodiscard]] bool operator==(const RegionChunkPos& other) const noexcept { return x == other.x && z == other.z; }

    [[nodiscard]] RegionChunkPos(int _x, int _z) noexcept : x(_x), z(_z) {}

    [[nodiscard]] explicit RegionChunkPos(WorldPos worldPos) noexcept {
        int regionX = worldPos.x < 0 ? ((worldPos.x + 1) / 256) - 1 : worldPos.x / 256;
        int regionZ = worldPos.z < 0 ? ((worldPos.z + 1) / 256) - 1 : worldPos.z / 256;
        int chunkX  = worldPos.x < 0 ? ((worldPos.x + 1) / 16) - 1 : worldPos.x / 16;
        int chunkZ  = worldPos.z < 0 ? ((worldPos.z + 1) / 16) - 1 : worldPos.z / 16;
        x           = regionX * 16 - chunkX;
        z           = regionZ * 16 - chunkZ;
    }

    [[nodiscard]] explicit RegionChunkPos(ChunkPosWithDim chunkPos) noexcept {
        int regionX = chunkPos.x < 0 ? ((chunkPos.x + 1) / 16) - 1 : chunkPos.x / 16;
        int regionZ = chunkPos.z < 0 ? ((chunkPos.z + 1) / 16) - 1 : chunkPos.z / 16;
        x           = regionX * 16 - chunkPos.x;
        z           = regionZ * 16 - chunkPos.z;
    }

    [[nodiscard]] explicit RegionChunkPos(ChunkPos chunkPos) noexcept {
        x = chunkPos.x < 0 ? ((chunkPos.x + 1) / 16) - 1 : chunkPos.x / 16;
        z = chunkPos.z < 0 ? ((chunkPos.z + 1) / 16) - 1 : chunkPos.z / 16;
    }
};

} // namespace map_demo