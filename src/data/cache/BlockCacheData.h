#pragma once

#include "data/BlockDataBase.h"


namespace map_demo {
class BlockCacheData : public BlockDataBase {
public:
    BlockColor bakedColor{0, 0, 0, 0};
};
} // namespace map_demo