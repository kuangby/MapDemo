#pragma once


#include "BlockCacheData.h"
#include "state/BlockColorManager.h"
#include "state/pos/ChunkWorldPos.h"

#include <array>
#include <shared_mutex>


namespace map_demo {

class ChunkCacheData {
public:
    std::uint64_t lastScanFrame = 0;

    bool                                           loadChunkBaseData = false;
    bool                                           loadBakedColors   = false;
    std::array<std::array<BlockCacheData, 16>, 16> blockData; // need to save

    mutable std::shared_mutex mutex_; // protects all fields above

public:
    void setColor(const ChunkWorldPos& pos, const BlockColor& color);

    [[nodiscard]] std::int16_t getHeight(const ChunkWorldPos& pos);

    [[nodiscard]] const BlockCacheData& getBlockCacheData(const ChunkWorldPos& pos) const;
    [[nodiscard]] BlockCacheData        getBlockCacheData(const ChunkWorldPos& pos);
};
} // namespace map_demo