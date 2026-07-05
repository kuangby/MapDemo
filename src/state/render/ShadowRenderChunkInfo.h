#pragma once

#include "state/cache/BlockCacheData.h"
#include "state/pos/ChunkWorldPos.h"
#include "state/render/ShadowRenderBlockInfo.h"

#include <array>


namespace map_demo {
class ShadowRenderChunkInfo {
public:
    std::array<std::array<ShadowRenderBlockInfo, 16>, 16> blocksInfo;

public:
    [[nodiscard]] const ShadowRenderBlockInfo& getBlockInfo(const ChunkWorldPos& pos) {
        return blocksInfo[pos.x][pos.z];
    }

    [[nodiscard]] const BlockCacheData& getBlockBaseInfo(const ChunkWorldPos& pos) {
        return blocksInfo[pos.x][pos.z].baseInfo;
    }
};
} // namespace map_demo