#pragma once


namespace map_demo {
class ChunkPosWithDim;
class ChunkWorldPos;

class WorldPos {
public:
    int x;
    int z;
    int dimId;

    [[nodiscard]] bool operator==(const WorldPos& other) const noexcept {
        return x == other.x && z == other.z && dimId == other.dimId;
    }

    [[nodiscard]] WorldPos(int _x, int _z, int _dimId) noexcept : x(_x), z(_z), dimId(_dimId) {}

    [[nodiscard]] WorldPos(ChunkPosWithDim chunkPos, ChunkWorldPos chunkWorldPos);
};

} // namespace map_demo