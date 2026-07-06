#include "WorldPos.h"
#include "ChunkPosWithDim.h"
#include "ChunkWorldPos.h"


namespace map_demo {
[[nodiscard]] WorldPos::WorldPos(ChunkPosWithDim chunkPos, ChunkWorldPos chunkWorldPos) {
    x     = chunkPos.x * 16 + chunkWorldPos.x;
    z     = chunkPos.z * 16 + chunkWorldPos.z;
    dimId = chunkPos.dimId;
}
} // namespace map_demo