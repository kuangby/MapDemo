#pragma once

#include "data/BlockDataBase.h"
#include "data/pos/ChunkWorldPos.h"


namespace map_demo {
class ChunkDataBase {
public:
    int shadowScale = -1;
    int minHeight   = -64;
    int maxHeight   = -64;

public:
    virtual ~ChunkDataBase() = default;

public:
    [[nodiscard]] virtual const BlockDataBase& getBlockBaseData(const ChunkWorldPos& pos) const = 0;

    [[nodiscard]] virtual const BlockDataBase& getBlockBaseData(const ChunkWorldPos& pos) = delete;
};
} // namespace map_demo