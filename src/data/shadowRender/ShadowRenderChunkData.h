#pragma once

#include "data/BlockDataBase.h"
#include "data/ChunkDataBase.h"
#include "data/cache/ChunkCacheData.h"
#include "data/pos/ChunkWorldPos.h"
#include "data/shadowRender/ShadowRenderBlockData.h"


#include <array>


namespace map_demo {
class ShadowRenderChunkData : public ChunkDataBase {
public:
    std::array<std::array<ShadowRenderBlockData, 16>, 16> blocksData;

public:
    explicit ShadowRenderChunkData(const ChunkCacheData& cacheData) {
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                blocksData[i][j] = ShadowRenderBlockData{cacheData.blocksData[i][j]};
            }
        }
    }

public:
    [[nodiscard]] const ShadowRenderBlockData& getBlockData(const ChunkWorldPos& pos) {
        return blocksData[pos.z][pos.x];
    }

    [[nodiscard]] const BlockDataBase& getBlockBaseData(const ChunkWorldPos& pos) const override {
        return blocksData[pos.z][pos.x];
    }
};
} // namespace map_demo