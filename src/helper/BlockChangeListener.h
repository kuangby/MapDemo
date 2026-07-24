#pragma once

#include "mc/world/level/BlockSourceListener.h"


namespace map_demo {
class BlockChangeListener : public BlockSourceListener {
public:
    void onBlockChanged(
        ::BlockSource&                 source,
        ::BlockPos const&              pos,
        uint                           layer,
        ::Block const&                 block,
        ::Block const&                 oldBlock,
        int                            updateFlags,
        ::ActorBlockSyncMessage const* syncMsg,
        ::BlockChangedEventTarget      eventTarget,
        ::Actor*                       blockChangeSource
    ) override {}

public:
    [[nodiscard]] static BlockChangeListener& getInstance() {
        static BlockChangeListener instance;
        return instance;
    }
};
} // namespace map_demo