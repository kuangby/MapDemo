#pragma once


#include "data/ChunkDataBase.h"
#include "data/cache/ChunkCacheData.h"
#include "data/cache/MapCacheManager.h"
#include "data/pos/ChunkPosWithDim.h"
#include "data/pos/ChunkWorldPos.h"
#include "data/pos/WorldPos.h"
#include "data/shadowRender/ShadowRenderChunkData.h"


#include <memory>
#include <unordered_map>


namespace map_demo {
// 区块阴影渲染器：以 chunk 为单位进行阴影烘焙
class ChunkShadowRenderer {
public:
    ChunkPosWithDim                      handlingChunkPos;
    std::shared_ptr<ShadowRenderChunkData> handlingChunk;
    std::unordered_map<ChunkPosWithDim, std::shared_ptr<const ChunkCacheData>>
        helperChunksData; // <offsetChunkPos, ChunkCacheData>

    // bake 期间高度查询统计：miss 表示邻 chunk 未加载，该方向的跨区块阴影会丢失
    int heightQueryCount = 0;
    int heightQueryMiss  = 0;

public:
    explicit ChunkShadowRenderer(const ChunkPosWithDim& pos) : handlingChunkPos(pos) {}

    // 加锁快照一份 ChunkData，离线烘焙后写回
    // softOnly：只重做 PCF 柔化与 bevel（复用已存 shadowOriginData，跳过射线采样）；
    // 无可复用阴影数据时自动回退全量烘焙
    void bake(const std::shared_ptr<ChunkCacheData>& data, bool softOnly = false);

public:
    [[nodiscard]] int getHeight(const WorldPos& offsetPos) {
        auto chunk = getChunk(offsetPos);
        ++heightQueryCount;
        if (!chunk) {
            ++heightQueryMiss;
            return -65;
        }
        return chunk->getBlockBaseData(ChunkWorldPos{offsetPos}).height;
    }

    [[nodiscard]] std::shared_ptr<const ChunkDataBase> getChunk(const WorldPos& offsetPos) {
        return getChunk(ChunkPosWithDim(offsetPos));
    }

    [[nodiscard]] std::shared_ptr<const ChunkDataBase> getChunk(const ChunkPosWithDim& offsetPos) {
        if (offsetPos.x == 0 && offsetPos.z == 0) return handlingChunk;
        auto [it, inserted] = helperChunksData.try_emplace(offsetPos);
        if (inserted) {
            auto chunkData = MapCacheManager::getInstance().getChunk(ChunkPosWithDim(
                handlingChunkPos.x + offsetPos.x,
                handlingChunkPos.z + offsetPos.z,
                handlingChunkPos.dimId
            ));
            if (chunkData && chunkData->loadChunkBaseData) {
                std::shared_lock<std::shared_mutex> lock(chunkData->mutex_);
                it->second = std::make_shared<const ChunkCacheData>(*chunkData);
            }
        }
        return it->second;
    }

    [[nodiscard]] std::shared_ptr<const ChunkDataBase>
    getChunkWithEffectiveShadowData(const ChunkPosWithDim& offsetPos, int scale) {
        auto chunk = getChunk(offsetPos);
        if (chunk && chunk->shadowScale == scale) return chunk;
        return nullptr;
    }

private:
    void applyStyle1();
    void applyStyle2();
    void applyWaterOverlay();
    void applyShadowMap(int scale);
    // PCF 柔化 + 汇总着色（applyShadowMap 的后半段，可独立于采样复用）
    void applyShadowBlur(int scale);
    void applyBevel(int scale);
};
} // namespace map_demo