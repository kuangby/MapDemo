#include "ChunkPosWithDim.h"
#include "RegionPos.h"


namespace map_demo {
[[nodiscard]] ChunkPosWithDim::ChunkPosWithDim(const RegionPos& regionPos, const ChunkPosWithDim& offset) noexcept {
    x     = regionPos.x * 16 + offset.x;
    z     = regionPos.z * 16 + offset.z;
    dimId = regionPos.dimId;
}
} // namespace map_demo