#pragma once


#include "BlockCacheData.h"
#include "data/BlockDataBase.h"
#include "data/ChunkDataBase.h"
#include "data/pos/ChunkWorldPos.h"

#include <array>
#include <shared_mutex>


namespace map_demo {

class ChunkCacheData : public ChunkDataBase {
public:
    std::uint64_t lastScanFrame = 0;

    bool loadChunkBaseData = false;
    bool loadBakedColors   = false;

    std::array<std::array<BlockCacheData, 16>, 16> blocksData; // need to save

    bool bakedDirty{false};

    // 每次 markBakedDirty 递增；bake 期间被重新标脏时 epoch 变化，用于避免清掉新脏标记
    std::uint32_t bakedDirtyEpoch{0};

    mutable std::shared_mutex mutex_; // protects all fields above

public:
    ChunkCacheData() = default;

    [[nodiscard]] ChunkCacheData(const ChunkCacheData& other)
    : ChunkDataBase(other),
      loadChunkBaseData(other.loadChunkBaseData),
      loadBakedColors(other.loadBakedColors),
      blocksData(other.blocksData) {}

public:
    void setColor(const ChunkWorldPos& pos, const BlockColor& color);

    [[nodiscard]] std::int16_t getHeight(const ChunkWorldPos& pos);

    [[nodiscard]] const BlockCacheData& getBlockCacheData(const ChunkWorldPos& pos) const;
    [[nodiscard]] BlockCacheData&       getBlockCacheData(const ChunkWorldPos& pos);

    [[nodiscard]] const BlockDataBase& getBlockBaseData(const ChunkWorldPos& pos) const override;

    void markBakedDirty() {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        bakedDirty = true;
        ++bakedDirtyEpoch;
    }

    bool takeBakedDirty() {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        if (!bakedDirty) return false;
        bakedDirty = false;
        return true;
    }

    [[nodiscard]] std::uint32_t getBakedDirtyEpoch() const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return bakedDirtyEpoch;
    }

    // 仅当 epoch 未变（bake 期间没有新的标脏）时才清除脏标记，返回是否清除成功
    bool takeBakedDirtyIfEpoch(std::uint32_t expectedEpoch) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        if (bakedDirtyEpoch != expectedEpoch) return false;
        bakedDirty = false;
        return true;
    }

    [[nodiscard]] bool isBakedDirty() const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return bakedDirty;
    }
};
} // namespace map_demo