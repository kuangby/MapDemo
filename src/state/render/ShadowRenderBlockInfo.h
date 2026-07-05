#pragma once

#include "state/cache/BlockCacheData.h"


namespace map_demo {
class ShadowRenderBlockInfo {
public:
    BlockCacheData baseInfo;
    std::string    blockName;           // 显示用的方块名
    std::string    solidBlockName;      // 水下固体方块名
    std::uint16_t  waterDepth{0};       // 0 = 无水
    BlockColor     waterSurfaceColor{}; // 水面颜色（已群系混合）


public:
    explicit ShadowRenderBlockInfo(BlockCacheData cacheData) : baseInfo(cacheData) {}
};
} // namespace map_demo