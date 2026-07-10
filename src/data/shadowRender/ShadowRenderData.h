#pragma once


#include "data/ChunkDataBase.h"
#include "data/cache/ChunkCacheData.h"
#include "data/pos/ChunkPosWithDim.h"
#include "data/pos/ChunkWorldPos.h"
#include "data/pos/RegionChunkPos.h"
#include "data/pos/RegionPos.h"
#include "data/pos/WorldPos.h"
#include "data/shadowRender/ShadowRenderChunkData.h"


#include <array>
#include <memory>
#include <unordered_map>


namespace map_demo {
// 用于阴影烘焙的区域辅助结构，16x16 chunks
class ShadowRenderData {
public:
    // static constexpr int SIZE   = RegionCacheData::SIZE; // 256
    // static constexpr int CHUNKS = RegionCacheData::CHUNKS; // 16
    // static constexpr int PIXELS = SIZE * SIZE;

    // std::vector<BlockColor>      terrain; // 256x256 RGBA
    // std::vector<BlockRenderInfo> info;    // 256x256 per-pixel info
    RegionPos                                                              handlingRegionPos;
    std::array<std::array<std::shared_ptr<ShadowRenderChunkData>, 16>, 16> handlingRegion; // 16x16 chunks
    std::unordered_map<ChunkPosWithDim, std::shared_ptr<const ChunkCacheData>>
        helperChunksData; // <offsetChunkPos, ChunkCacheData>

public:
    explicit ShadowRenderData(const RegionPos& pos) : handlingRegionPos(pos) {}

public:
    [[nodiscard]] std::shared_ptr<ShadowRenderChunkData> getLocalShadowChunkData(const RegionChunkPos& chunkPos) {
        return handlingRegion[chunkPos.z][chunkPos.x];
    }

    // [[nodiscard]] std::shared_ptr<RegionCacheData> getHelperRegion(const RegionPos& offsetPos) {
    //     RegionPos actualPos =
    //         {handlingRegionPos.x + offsetPos.x, handlingRegionPos.z + offsetPos.z, handlingRegionPos.dimId};
    //     auto [it, inserted] = helperRegions.try_emplace(actualPos);
    //     // 确保一次bake期间，用到的helperRegion不发生变化，所以 !inserted && it->second == nullptr 的情况不做处理
    //     if (inserted) it->second = MapCacheManager::getInstance().getRegion(actualPos);
    //     return it->second;
    // }

    [[nodiscard]] const BlockDataBase* getBlockBaseData(const WorldPos& offsetPos) {
        if (offsetPos.x >= 0 && offsetPos.x < 256 && offsetPos.z >= 0 && offsetPos.z < 256)
            return &getLocalShadowChunkData(RegionChunkPos{offsetPos})->getBlockBaseData(ChunkWorldPos{offsetPos});
        // auto offsetRegionPos = RegionPos{offsetPos};
        auto it = helperChunksData.find(ChunkPosWithDim{offsetPos});
        if (it == helperChunksData.end()) return nullptr;
        return &it->second->getBlockBaseData(ChunkWorldPos{offsetPos});
    }

    [[nodiscard]] std::shared_ptr<const ChunkDataBase> getChunk(const WorldPos& offsetPos) {
        return getChunk(ChunkPosWithDim(offsetPos));
    }

    [[nodiscard]] std::shared_ptr<const ChunkDataBase> getChunk(const ChunkPosWithDim& offsetPos) {
        if (offsetPos.x >= 0 && offsetPos.x < 16 && offsetPos.z >= 0 && offsetPos.z < 16)
            return getLocalShadowChunkData(RegionChunkPos{offsetPos});
        auto it = helperChunksData.find(offsetPos);
        if (it == helperChunksData.end()) return nullptr;
        return it->second;
    }
    [[nodiscard]] std::shared_ptr<const ChunkDataBase> getHelperChunkWithShadowData(const ChunkPosWithDim& offsetPos) {
        auto it = helperChunksData.find(offsetPos);
        if (it == helperChunksData.end() || !it->second->loadShadowData) return nullptr;
        return it->second;
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