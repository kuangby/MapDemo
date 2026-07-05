#pragma once


#include "state/cache/BlockCacheData.h"
#include "state/cache/ChunkCacheData.h"
#include "state/pos/ChunkPosWithDim.h"
#include "state/pos/ChunkWorldPos.h"
#include "state/pos/RegionChunkPos.h"
#include "state/pos/RegionPos.h"
#include "state/pos/WorldPos.h"
#include "state/render/ShadowRenderChunkInfo.h"


#include <array>
#include <memory>
#include <optional>
#include <unordered_map>


namespace map_demo {
// 用于阴影烘焙的区域辅助结构，16x16 chunks
struct ShadowRenderData {
    // static constexpr int SIZE   = RegionCacheData::SIZE; // 256
    // static constexpr int CHUNKS = RegionCacheData::CHUNKS; // 16
    // static constexpr int PIXELS = SIZE * SIZE;

    // std::vector<BlockColor>      terrain; // 256x256 RGBA
    // std::vector<BlockRenderInfo> info;    // 256x256 per-pixel info
    RegionPos                                                              handlingRegionPos;
    std::array<std::array<std::shared_ptr<ShadowRenderChunkInfo>, 16>, 16> handlingRegion; // 16x16 chunks
    std::unordered_map<ChunkPosWithDim, std::unique_ptr<const ChunkCacheData>>
        helperChunksData; // <offsetChunkPos, ChunkCacheData>

    explicit ShadowRenderData(const RegionPos& pos) : handlingRegionPos(pos) {
        for (auto& row : handlingRegion) {
            for (auto& chunk : row) {
                chunk = std::make_shared<ShadowRenderChunkInfo>();
            }
        }
    }

    [[nodiscard]] std::shared_ptr<ShadowRenderChunkInfo> getLocalShadowChunkData(const RegionChunkPos& chunkPos) {
        return handlingRegion[chunkPos.x][chunkPos.z];
    }

    // [[nodiscard]] std::shared_ptr<RegionCacheData> getHelperRegion(const RegionPos& offsetPos) {
    //     RegionPos actualPos =
    //         {handlingRegionPos.x + offsetPos.x, handlingRegionPos.z + offsetPos.z, handlingRegionPos.dimId};
    //     auto [it, inserted] = helperRegions.try_emplace(actualPos);
    //     // 确保一次bake期间，用到的helperRegion不发生变化，所以 !inserted && it->second == nullptr 的情况不做处理
    //     if (inserted) it->second = MapCacheManager::getInstance().getRegion(actualPos);
    //     return it->second;
    // }

    [[nodiscard]] std::optional<BlockCacheData> getBlockBaseInfo(const WorldPos& offsetPos) {
        if (offsetPos.x >= 0 && offsetPos.x < 256 && offsetPos.z >= 0 && offsetPos.z < 256)
            return getLocalShadowChunkData(RegionChunkPos{offsetPos})->getBlockBaseInfo(ChunkWorldPos{offsetPos});
        // auto offsetRegionPos = RegionPos{offsetPos};
        auto it = helperChunksData.find(ChunkPosWithDim{offsetPos});
        if (it == helperChunksData.end()) return std::nullopt;
        return it->second->getBlockCacheData(ChunkWorldPos{offsetPos});
    }

    // [[nodiscard]] BlockColor getPixel(int x, int z) const {
    //     return chunksData[z / 16][x / 16]->info[z % 16][x % 16].color;
    // }
    // void setPixel(int x, int z, BlockColor c) { chunksData[z / 16][x / 16]->info[z % 16][x % 16].color = c; }

    // [[nodiscard]] const BlockRenderInfo& getInfo(int x, int z) const {
    //     return chunksData[z / 16][x / 16]->info[z % 16][x % 16];
    // }
    // void setInfo(int x, int z, const BlockRenderInfo& i) { chunksData[z / 16][x / 16]->info[z % 16][x % 16] = i; }

    // [[nodiscard]] int16_t getHeight(int x, int z) const { return getInfo(x, z).height; }
    // [[nodiscard]] int16_t getSolidHeight(int x, int z) const { return getInfo(x, z).solidHeight; }
    // [[nodiscard]] bool    hasData(int x, int z) const { return getInfo(x, z).hasData; }
};
} // namespace map_demo