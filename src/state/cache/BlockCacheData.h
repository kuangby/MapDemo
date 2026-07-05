#pragma once

#include "state/BlockColorManager.h"


namespace map_demo {
class BlockCacheData {
public:
    BlockColor color;
    short      height      = -128;
    short      solidHeight = -128;
    BlockColor bakedColor;
};
} // namespace map_demo