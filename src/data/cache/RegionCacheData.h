#pragma once


#include "data/cache/ChunkCacheData.h"
#include "data/pos/RegionChunkPos.h"
#include <memory>
#include <shared_mutex>
#include <vector>


namespace coral_map {
class RegionCacheData {
private:
    std::array<std::array<std::shared_ptr<ChunkCacheData>, 16>, 16> chunksData;
    mutable std::shared_mutex                                       mutex_; // protects all fields above
    bool                                                            bakedDirty{false};
    int                                                             delay{0};
    int                                                             maxDelay{0};
    bool                                                            everBaked{false};

public:
    std::shared_ptr<ChunkCacheData> getChunkData(const RegionChunkPos& pos) const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return chunksData[pos.z][pos.x];
    }

    std::shared_ptr<ChunkCacheData> getOrCreateChunkData(const RegionChunkPos& pos) {
        {
            std::shared_lock<std::shared_mutex> lock(mutex_);
            auto&                               chunk = chunksData[pos.z][pos.x];
            if (chunk) return chunk;
        } // 读锁在此释放

        std::unique_lock<std::shared_mutex> lock(mutex_);
        auto&                               chunk = chunksData[pos.z][pos.x];
        if (!chunk) // 二次检查，防止其他线程已创建
            chunk = std::make_shared<ChunkCacheData>();
        return chunk;
    }

    void markBakedDirty() {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        if (!bakedDirty) {
            bakedDirty = true;
            delay      = 10;
            maxDelay   = 60;
        } else if (delay > 0) {
            delay = 10;
        }
    }

    bool takeBakedDirty() {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        if (!bakedDirty) return false;
        bakedDirty = false;
        delay      = 0;
        maxDelay   = 0;
        return true;
    }

    void resetBakedDirty() {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        bakedDirty = false;
        delay      = 0;
        maxDelay   = 0;
    }

    bool tickBakedDirty() {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        if (!bakedDirty || delay == 0 || maxDelay == 0) return false;
        --delay;
        --maxDelay;
        return delay == 0 || maxDelay == 0;
    }

    [[nodiscard]] bool isBakedDirty() const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return bakedDirty;
    }

    void collectDirtyChunks(std::vector<RegionChunkPos>& out) const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        for (int z = 0; z < 16; ++z) {
            for (int x = 0; x < 16; ++x) {
                auto& chunk = chunksData[z][x];
                if (chunk && chunk->isBakedDirty()) out.emplace_back(x, z);
            }
        }
    }

    // 收集仅柔化级脏（softDirty 且非 full dirty）的 chunk
    void collectSoftDirtyChunks(std::vector<RegionChunkPos>& out) const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        for (int z = 0; z < 16; ++z) {
            for (int x = 0; x < 16; ++x) {
                auto& chunk = chunksData[z][x];
                if (chunk && chunk->isBakedSoftDirty() && !chunk->isBakedDirty()) out.emplace_back(x, z);
            }
        }
    }

    void markEverBaked() {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        everBaked = true;
    }

    [[nodiscard]] bool hasEverBaked() const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return everBaked;
    }
};
} // namespace coral_map