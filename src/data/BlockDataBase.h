#pragma once

#include "data/BlockColor.h"
#include <vector>


namespace map_demo {
class BlockDataBase {
public:
    BlockColor                      color;
    short                           height      = -128;
    short                           solidHeight = -128;
    std::vector<std::vector<float>> shadowOriginData;

public:
    virtual ~BlockDataBase() = default;
};
} // namespace map_demo