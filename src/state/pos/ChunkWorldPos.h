#pragma once

#include "WorldPos.h"


namespace map_demo {
class ChunkWorldPos {
public:
    int x;
    int z;

    [[nodiscard]] bool operator==(const ChunkWorldPos& other) const noexcept { return x == other.x && z == other.z; }

    [[nodiscard]] ChunkWorldPos(int _x, int _z) noexcept : x(_x), z(_z) {}

    [[nodiscard]] explicit ChunkWorldPos(WorldPos worldPos) noexcept {
        int chunkX = worldPos.x < 0 ? ((worldPos.x + 1) / 16) - 1 : worldPos.x / 16;
        int chunkZ = worldPos.z < 0 ? ((worldPos.z + 1) / 16) - 1 : worldPos.z / 16;
        x          = chunkX * 16 - worldPos.x;
        z          = chunkZ * 16 - worldPos.z;
    }
};

} // namespace map_demo