#pragma once

#include "data/BlockDataBase.h"

#include <cstdint>


namespace coral_map {
class BlockCacheData : public BlockDataBase {
public:
    BlockColor   bakedColor{0, 0, 0, 0};
    // 透明水拆分：color 存水下固体色，水面色与水深单独存，烘焙期阴影后再叠加
    std::uint8_t waterDepth = 0; // 0 = 无水
    BlockColor   waterSurfaceColor{0, 0, 0, 0};
};
} // namespace coral_map