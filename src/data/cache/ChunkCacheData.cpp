#include "ChunkCacheData.h"
#include "data/BlockDataBase.h"
#include <mutex>
#include <shared_mutex>

namespace map_demo {
void ChunkCacheData::setColor(const ChunkWorldPos& pos, const BlockColor& color) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    blocksData[pos.z][pos.x].color = color;
}

[[nodiscard]] std::int16_t ChunkCacheData::getHeight(const ChunkWorldPos& pos) {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return blocksData[pos.z][pos.x].height;
}

[[nodiscard]] const BlockCacheData& ChunkCacheData::getBlockCacheData(const ChunkWorldPos& pos) const {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return blocksData[pos.z][pos.x];
}

[[nodiscard]] BlockCacheData& ChunkCacheData::getBlockCacheData(const ChunkWorldPos& pos) {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return blocksData[pos.z][pos.x];
}

[[nodiscard]] const BlockDataBase& ChunkCacheData::getBlockBaseData(const ChunkWorldPos& pos) const {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return blocksData[pos.z][pos.x];
}
} // namespace map_demo