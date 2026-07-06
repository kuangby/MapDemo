#pragma once

#include "data/BlockDataBase.h"
#include "data/cache/BlockCacheData.h"

#include <string>


namespace map_demo {
class ShadowRenderBlockData : public BlockDataBase {
public:
    std::string   blockName;         // 显示用的方块名
    std::string   solidBlockName;    // 水下固体方块名
    std::uint16_t waterDepth = 0;    // 0 = 无水
    BlockColor    waterSurfaceColor; // 水面颜色（已群系混合）


public:
    ShadowRenderBlockData() = default;

    explicit ShadowRenderBlockData(const BlockCacheData& cacheData)
    : BlockDataBase(static_cast<const BlockDataBase&>(cacheData)) {}
};
} // namespace map_demo