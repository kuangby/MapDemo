#pragma once

#include "state/BlockColorManager.h"
#include "state/ChunkManager.h"

#include <cstdint>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

namespace map_demo {

// Region coordinate: each region contains 16x16 chunks (256x256 blocks)
struct RegionPos {
    int x;
    int z;
    int dim;

    bool operator==(const RegionPos& other) const noexcept {
        return x == other.x && z == other.z && dim == other.dim;
    }
};

} // namespace map_demo

namespace std {

template <>
struct hash<map_demo::RegionPos> {
    std::size_t operator()(const map_demo::RegionPos& p) const noexcept {
        return ((static_cast<std::uint64_t>(static_cast<std::uint32_t>(p.x)) << 32) |
                static_cast<std::uint64_t>(static_cast<std::uint32_t>(p.z))) ^
               (static_cast<std::uint64_t>(p.dim) << 48);
    }
};

} // namespace std

namespace map_demo {

// Per-region surface color cache, 256x256 pixels RGBA
struct RegionData {
    static constexpr int SIZE      = 16 * 16; // 256x256 blocks
    static constexpr int BYTES     = SIZE * SIZE * 4;
    static constexpr int CHUNKS    = 16;      // chunks per side

    std::vector<std::uint8_t>  colors;              // RGBA
    std::vector<std::uint64_t> chunkLastScanFrame;  // 16x16 chunks
    bool dirty{true};

    RegionData() : colors(BYTES, 0), chunkLastScanFrame(CHUNKS * CHUNKS, 0) {}

    void setPixel(int localX, int localZ, BlockColor c) {
        int idx = (localZ * SIZE + localX) * 4;
        colors[idx + 0] = c.r;
        colors[idx + 1] = c.g;
        colors[idx + 2] = c.b;
        colors[idx + 3] = c.a;
    }

    [[nodiscard]] BlockColor getPixel(int localX, int localZ) const {
        int idx = (localZ * SIZE + localX) * 4;
        return BlockColor{colors[idx + 0], colors[idx + 1], colors[idx + 2], colors[idx + 3]};
    }

    void clearChunk(int chunkLocalX, int chunkLocalZ) {
        int startX = chunkLocalX * 16;
        int startZ = chunkLocalZ * 16;
        for (int z = 0; z < 16; ++z) {
            for (int x = 0; x < 16; ++x) {
                setPixel(startX + x, startZ + z, BlockColor{0, 0, 0, 0});
            }
        }
        chunkLastScanFrame[chunkLocalZ * CHUNKS + chunkLocalX] = 0;
        dirty = true;
    }

    [[nodiscard]] bool isEmpty() const {
        for (auto v : chunkLastScanFrame) {
            if (v != 0) return false;
        }
        return true;
    }

    void setChunkLastScanFrame(int chunkLocalX, int chunkLocalZ, std::uint64_t frame) {
        chunkLastScanFrame[chunkLocalZ * CHUNKS + chunkLocalX] = frame;
    }

    [[nodiscard]] std::uint64_t getChunkLastScanFrame(int chunkLocalX, int chunkLocalZ) const {
        return chunkLastScanFrame[chunkLocalZ * CHUNKS + chunkLocalX];
    }
};

class MapCacheManager {
public:
    static MapCacheManager& getInstance();

    // Clear all cached regions (e.g. on world change)
    void clearAll();

    // Get or create a region
    RegionData* getRegion(int regionX, int regionZ, int dim);
    RegionData* getRegion(const RegionPos& pos);

    // Convert world coordinates to region coordinates
    [[nodiscard]] static RegionPos worldToRegion(int worldX, int worldZ, int dim);

    // Convert region coordinates to its min chunk coordinates
    [[nodiscard]] static ChunkPos regionToMinChunk(const RegionPos& pos);

    // Update a single block color in cache
    void updateBlock(int worldX, int worldZ, int dim, BlockColor color);

    // Mark a region dirty
    void markDirty(int regionX, int regionZ, int dim);

    // Evict a single chunk from cache. Removes the whole region if it becomes empty.
    void evictChunk(int chunkX, int chunkZ, int dim);

    // Evict an entire region (kept for compatibility)
    void evictRegion(int regionX, int regionZ, int dim);
    void evictRegion(const RegionPos& pos);

private:
    MapCacheManager() = default;

    std::unordered_map<RegionPos, std::unique_ptr<RegionData>> regions_;
    std::mutex mutex_;
};

} // namespace map_demo
