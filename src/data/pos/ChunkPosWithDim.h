#pragma once

#include "WorldPos.h"
#include "mc/world/level/ChunkPos.h"


namespace map_demo {
class ChunkPosWithDim {
public:
    int x;
    int z;
    int dimId;

    [[nodiscard]] bool operator==(const ChunkPosWithDim& other) const noexcept {
        return x == other.x && z == other.z && dimId == other.dimId;
    }

    [[nodiscard]] explicit ChunkPosWithDim(WorldPos worldPos) noexcept {
        x     = worldPos.x < 0 ? ((worldPos.x + 1) / 16) - 1 : worldPos.x / 16;
        z     = worldPos.z < 0 ? ((worldPos.z + 1) / 16) - 1 : worldPos.z / 16;
        dimId = worldPos.dimId;
    }

    [[nodiscard]] ChunkPosWithDim() noexcept : x(0), z(0), dimId(0) {}

    [[nodiscard]] ChunkPosWithDim(int _x, int _z, int _dimId) noexcept : x(_x), z(_z), dimId(_dimId) {}

    [[nodiscard]] explicit ChunkPosWithDim(ChunkPos chunkPos, int dimId) noexcept {
        x           = chunkPos.x;
        z           = chunkPos.z;
        this->dimId = dimId;
    }

    [[nodiscard]] explicit ChunkPosWithDim(const RegionPos& regionPos, const ChunkPosWithDim& offset) noexcept;
};
} // namespace map_demo


namespace std {
template <>
struct hash<map_demo::ChunkPosWithDim> {
    std::size_t operator()(const map_demo::ChunkPosWithDim& k) const noexcept {
        std::uint64_t v = (static_cast<std::uint64_t>(static_cast<std::uint32_t>(k.x)) << 32)
                        | static_cast<std::uint64_t>(static_cast<std::uint32_t>(k.z));
        return v ^ (static_cast<std::uint64_t>(k.dimId) << 48);
    }
};

} // namespace std