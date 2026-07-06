#pragma once


#include "data/cache/ChunkCacheData.h"
#include "data/pos/RegionChunkPos.h"
#include <memory>
#include <shared_mutex>


namespace map_demo {
class RegionCacheData {
private:
    std::array<std::array<std::shared_ptr<ChunkCacheData>, 16>, 16> chunksData;
    mutable std::shared_mutex                                       mutex_; // protects all fields above
    bool                                                            dirty{true};
    bool                                                            bakedDirty{true};

public:
    std::shared_ptr<ChunkCacheData> getChunkData(const RegionChunkPos& pos) const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return chunksData[pos.x][pos.z];
    }

    std::shared_ptr<ChunkCacheData> getOrCreateChunkData(const RegionChunkPos& pos) {
        {
            std::shared_lock<std::shared_mutex> lock(mutex_);
            auto&                               chunk = chunksData[pos.x][pos.z];
            if (chunk) return chunk;
        } // 读锁在此释放

        std::unique_lock<std::shared_mutex> lock(mutex_);
        auto&                               chunk = chunksData[pos.x][pos.z];
        if (!chunk) // 二次检查，防止其他线程已创建
            chunk = std::make_shared<ChunkCacheData>();
        return chunk;
    }

    void markBakedDirty() {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        bakedDirty = true;
    }

    void markDirty() {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        dirty = true;
    }

    void resetBakedDirty() {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        bakedDirty = false;
    }

    void resetDirty() {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        dirty = false;
    }

    [[nodiscard]] bool isDirty() const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return dirty;
    }

    [[nodiscard]] bool isBakedDirty() const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return bakedDirty;
    }
};
} // namespace map_demo