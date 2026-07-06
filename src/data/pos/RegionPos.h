#pragma once

#include "ChunkPosWithDim.h"
#include "WorldPos.h"


namespace map_demo {
class RegionPos {
public:
    int x     = 0;
    int z     = 0;
    int dimId = -1;

    [[nodiscard]] bool operator==(const RegionPos& other) const noexcept {
        return x == other.x && z == other.z && dimId == other.dimId;
    }

    [[nodiscard]] RegionPos() = default;

    [[nodiscard]] RegionPos(int _x, int _y, int _dim) noexcept : x(_x), z(_y), dimId(_dim) {}


    [[nodiscard]] explicit RegionPos(WorldPos worldPos) noexcept {
        x     = worldPos.x < 0 ? ((worldPos.x + 1) / 256) - 1 : worldPos.x / 256;
        z     = worldPos.z < 0 ? ((worldPos.z + 1) / 256) - 1 : worldPos.z / 256;
        dimId = worldPos.dimId;
    }

    [[nodiscard]] explicit RegionPos(ChunkPosWithDim pos) noexcept {
        x     = pos.x < 0 ? ((pos.x + 1) / 16) - 1 : pos.x / 16;
        z     = pos.z < 0 ? ((pos.z + 1) / 16) - 1 : pos.z / 16;
        dimId = pos.dimId;
    }
};
} // namespace map_demo


namespace std {
template <>
struct hash<map_demo::RegionPos> {
    std::size_t operator()(const map_demo::RegionPos& p) const noexcept {
        return ((static_cast<std::uint64_t>(static_cast<std::uint32_t>(p.x)) << 32)
                | static_cast<std::uint64_t>(static_cast<std::uint32_t>(p.z)))
             ^ (static_cast<std::uint64_t>(p.dimId) << 48);
    }
};
} // namespace std
