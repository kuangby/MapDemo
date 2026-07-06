#pragma once

#include "data/BlockColor.h"


namespace map_demo {
class BlockDataBase {
public:
    BlockColor color;
    short      height      = -128;
    short      solidHeight = -128;

public:
    virtual ~BlockDataBase() = default;
};
} // namespace map_demo