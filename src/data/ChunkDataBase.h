#pragma once

#include "data/BlockDataBase.h"
#include "data/pos/ChunkWorldPos.h"


namespace map_demo {
class ChunkDataBase {
public:
    virtual ~ChunkDataBase() = default;

public:
    [[nodiscard]] virtual const BlockDataBase& getBlockBaseData(const ChunkWorldPos& pos) const = 0;

    [[nodiscard]] virtual const BlockDataBase& getBlockBaseData(const ChunkWorldPos& pos) = delete;
};
} // namespace map_demo