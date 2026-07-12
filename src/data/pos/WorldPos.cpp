#include "WorldPos.h"
#include "ChunkPosWithDim.h"
#include "ChunkWorldPos.h"
#include "RegionChunkPos.h"
#include "RegionPos.h"


namespace map_demo {
[[nodiscard]] WorldPos::WorldPos(const ChunkPosWithDim& chunkPos, const ChunkWorldPos& chunkWorldPos) noexcept {
    x     = chunkPos.x * 16 + chunkWorldPos.x;
    z     = chunkPos.z * 16 + chunkWorldPos.z;
    dimId = chunkPos.dimId;
}

[[nodiscard]] WorldPos::WorldPos(
    const RegionPos&      regionPos,
    const RegionChunkPos& chunkPos,
    const ChunkWorldPos&  chunkWorldPos
) noexcept {
    x     = regionPos.x * 256 + chunkPos.x * 16 + chunkWorldPos.x;
    z     = regionPos.z * 256 + chunkPos.z * 16 + chunkWorldPos.z;
    dimId = regionPos.dimId;
}
} // namespace map_demo