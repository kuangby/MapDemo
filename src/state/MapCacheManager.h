#pragma once

#include "state/BlockColorManager.h"
#include "state/ChunkManager.h"

#include <array>
#include <atomic>
#include <cstdint>
#include <ll/api/data/KeyValueDB.h>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <unordered_map>
#include <vector>


namespace map_demo {

// Region coordinate: each region contains 16x16 chunks (256x256 blocks)
struct RegionPos {
    int x;
    int z;
    int dim;

    bool operator==(const RegionPos& other) const noexcept { return x == other.x && z == other.z && dim == other.dim; }
};

} // namespace map_demo

namespace std {

template <>
struct hash<map_demo::RegionPos> {
    std::size_t operator()(const map_demo::RegionPos& p) const noexcept {
        return ((static_cast<std::uint64_t>(static_cast<std::uint32_t>(p.x)) << 32)
                | static_cast<std::uint64_t>(static_cast<std::uint32_t>(p.z)))
             ^ (static_cast<std::uint64_t>(p.dim) << 48);
    }
};

} // namespace std

namespace map_demo {

struct ChunkData {
    std::uint64_t lastScanFrame = 0;

    bool                                         loadChunkBaseData = false;
    std::array<std::array<BlockColor, 16>, 16>   colors;
    std::array<std::array<std::int16_t, 16>, 16> heights;
    std::array<std::array<std::int16_t, 16>, 16> solidHeights;
    std::array<std::array<std::int16_t, 16>, 16> waterDepths;

    bool                                       loadBakedColors = false;
    std::array<std::array<BlockColor, 16>, 16> bakedColors; // need to save

    mutable std::shared_mutex mutex_; // protects all fields above

    void loadBaseData(const ChunkData& chunk) {}
};

// Per-region surface color cache, 256x256 pixels RGBA
struct RegionData {
    static constexpr int SIZE   = 16 * 16; // 256x256 blocks
    static constexpr int PIXELS = SIZE * SIZE;
    static constexpr int BYTES  = PIXELS * 4;
    static constexpr int CHUNKS = 16; // chunks per side

    // std::vector<std::uint8_t>  colors;             // RGBA
    // std::vector<std::uint64_t> chunkLastScanFrame; // 16x16 chunks
    // std::vector<std::uint8_t>  bakedColors;        // 256x256 RGBA after shadow baking
    // std::vector<std::int16_t>  heights;            // 256x256 surface height (mHeightmap)
    // std::vector<std::int16_t>  solidHeights;       // 256x256 solid height (mRenderHeightmap)
    // std::vector<std::uint8_t>  waterDepths;        // 256x256 water depth
    std::array<std::array<std::shared_ptr<ChunkData>, 16>, 16> chunkData;
    bool                                                       dirty{true};
    bool                                                       bakedDirty{true};
    mutable std::shared_mutex                                  mutex_; // protects all fields above

    void loadBaseData(int chunkLocalX, int chunkLocalZ, const ChunkData& chunk) {}

    // bool setHeight(int localX, int localZ, std::int16_t h) {
    //     std::unique_lock<std::shared_mutex> lock(mutex_);
    //     auto&                               chunk = chunkData[localZ / 16][localX / 16];
    //     if (chunk.has_value()) {
    //         chunk.value().heights[localZ % 16][localX % 16] = h;
    //         return true;
    //     } else return false;
    // }

    [[nodiscard]] std::optional<std::int16_t> getHeight(int localX, int localZ) const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        auto&                               chunk = chunkData[localZ / 16][localX / 16];
        if (chunk.has_value()) {
            return chunk.value().heights[localZ % 16][localX % 16];
        } else return std::nullopt;
    }

    // void setSolidHeight(int localX, int localZ, std::int16_t h) {
    //     std::unique_lock<std::shared_mutex> lock(mutex_);
    //     solidHeights[localZ * SIZE + localX] = h;
    // }

    [[nodiscard]] std::int16_t getSolidHeight(int localX, int localZ) const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return solidHeights[localZ * SIZE + localX];
    }

    // void setWaterDepth(int localX, int localZ, std::uint8_t depth) {
    //     std::unique_lock<std::shared_mutex> lock(mutex_);
    //     waterDepths[localZ * SIZE + localX] = depth;
    // }

    [[nodiscard]] std::uint8_t getWaterDepth(int localX, int localZ) const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return waterDepths[localZ * SIZE + localX];
    }

    // void setBakedPixel(int localX, int localZ, BlockColor c) {
    //     int                                 idx = (localZ * SIZE + localX) * 4;
    //     std::unique_lock<std::shared_mutex> lock(mutex_);
    //     bakedColors[idx + 0] = c.r;
    //     bakedColors[idx + 1] = c.g;
    //     bakedColors[idx + 2] = c.b;
    //     bakedColors[idx + 3] = c.a;
    // }

    [[nodiscard]] BlockColor getBakedPixel(int localX, int localZ) const {
        int                                 idx = (localZ * SIZE + localX) * 4;
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return BlockColor{bakedColors[idx + 0], bakedColors[idx + 1], bakedColors[idx + 2], bakedColors[idx + 3]};
    }

    void markBakedDirty() { bakedDirty = true; }

    // void setPixel(int localX, int localZ, BlockColor c) {
    //     int                                 idx = (localZ * SIZE + localX) * 4;
    //     std::unique_lock<std::shared_mutex> lock(mutex_);
    //     colors[idx + 0] = c.r;
    //     colors[idx + 1] = c.g;
    //     colors[idx + 2] = c.b;
    //     colors[idx + 3] = c.a;
    // }

    [[nodiscard]] BlockColor getPixel(int localX, int localZ) const {
        int                                 idx = (localZ * SIZE + localX) * 4;
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return BlockColor{colors[idx + 0], colors[idx + 1], colors[idx + 2], colors[idx + 3]};
    }

    // void clearChunk(int chunkLocalX, int chunkLocalZ) {
    //     int                                 startX = chunkLocalX * 16;
    //     int                                 startZ = chunkLocalZ * 16;
    //     std::unique_lock<std::shared_mutex> lock(mutex_);
    //     for (int z = 0; z < 16; ++z) {
    //         for (int x = 0; x < 16; ++x) {
    //             int idx                                          = ((startZ + z) * SIZE + (startX + x)) * 4;
    //             colors[idx + 0]                                  = 0;
    //             colors[idx + 1]                                  = 0;
    //             colors[idx + 2]                                  = 0;
    //             colors[idx + 3]                                  = 0;
    //             bakedColors[idx + 0]                             = 0;
    //             bakedColors[idx + 1]                             = 0;
    //             bakedColors[idx + 2]                             = 0;
    //             bakedColors[idx + 3]                             = 0;
    //             heights[(startZ + z) * SIZE + (startX + x)]      = -128;
    //             solidHeights[(startZ + z) * SIZE + (startX + x)] = -128;
    //             waterDepths[(startZ + z) * SIZE + (startX + x)]  = 0;
    //         }
    //     }
    //     chunkLastScanFrame[chunkLocalZ * CHUNKS + chunkLocalX] = 0;
    //     dirty                                                  = true;
    //     bakedDirty                                             = true;
    // }

    // [[nodiscard]] bool isEmpty() const {
    //     std::shared_lock<std::shared_mutex> lock(mutex_);
    //     for (auto v : chunkLastScanFrame) {
    //         if (v != 0) return false;
    //     }
    //     return true;
    // }

    void setChunkLastScanFrame(int chunkLocalX, int chunkLocalZ, std::uint64_t frame) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        chunkLastScanFrame[chunkLocalZ * CHUNKS + chunkLocalX] = frame;
    }

    [[nodiscard]] std::uint64_t getChunkLastScanFrame(int chunkLocalX, int chunkLocalZ) const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return chunkLastScanFrame[chunkLocalZ * CHUNKS + chunkLocalX];
    }
};

class MapCacheManager {
public:
    static MapCacheManager& getInstance();

    // Clear all cached regions (e.g. on world change)
    void clearAll();

    // Get or create a region
    std::shared_ptr<RegionData> getOrCreateRegion(int regionX, int regionZ, int dim);
    std::shared_ptr<RegionData> getOrCreateRegion(const RegionPos& pos);

    std::shared_ptr<ChunkData> getOrCreateChunk(const ChunkPos& pos, int dimId);

    // Convert world coordinates to region coordinates
    [[nodiscard]] static RegionPos worldToRegion(int worldX, int worldZ, int dim);

    // Update a single block color in cache
    void updateBlock(int worldX, int worldZ, int dim, BlockColor color);

    // Mark a region dirty
    void markDirty(int regionX, int regionZ, int dim);

    // Evict a single chunk from cache. Removes the whole region if it becomes empty.
    // void evictChunk(int chunkX, int chunkZ, int dim);

    // Evict an entire region (kept for compatibility)
    void evictRegion(int regionX, int regionZ, int dim);
    void evictRegion(const RegionPos& pos);

    // 初始化磁盘缓存，path 为 KeyValueDB 目录
    bool initializeDiskCache(const std::filesystem::path& path);

    // 磁盘缓存读写
    void               saveToDisk(const RegionPos& regionPos, std::shared_ptr<RegionData> data);
    bool               loadFromDisk(const RegionPos& regionPos, std::shared_ptr<RegionData> data);
    static std::string makeDiskKey(const RegionPos& regionPos);
    std::string        serializeRegionData(std::shared_ptr<RegionData> data);
    bool               deserializeRegionData(std::shared_ptr<RegionData> data, const std::string& blob);

    void evictRegionsOutsideRadius(int centerChunkX, int centerChunkZ, int dim, int radiusChunks);

private:
    MapCacheManager() = default;

    std::unordered_map<RegionPos, std::shared_ptr<RegionData>> regions_;
    std::mutex                                                 mutex_;

    // 磁盘缓存
    std::unique_ptr<ll::data::KeyValueDB> diskCache_;
};

} // namespace map_demo
