#pragma once

#include <ll/api/memory/Hook.h>
#include <mc/client/game/ClientInstance.h>
#include <mc/client/player/LocalPlayer.h>
#include <mc/world/level/BlockPos.h>
#include <mc/world/level/BlockSource.h>
#include <mc/world/level/ChunkBlockPos.h>
#include <mc/world/level/ChunkLocalHeight.h>
#include <mc/world/level/biome/Biome.h>
#include <mc/world/level/block/Block.h>
#include <mc/world/level/chunk/ChunkState.h>
#include <mc/world/level/chunk/LevelChunk.h>
#include <mc/world/level/dimension/Dimension.h>


#include "config/Config.h"
#include "data/cache/MapCacheManager.h"
#include "mod/MapDemo.h"
#include "state/MapState.h"
#include "state/TerrainScanner.h"
#include "state/render/RegionRenderer.h"


namespace map_demo {

LL_TYPE_INSTANCE_HOOK(
    ClientInstanceUpdateHook,
    ll::memory::HookPriority::Normal,
    ClientInstance,
    &ClientInstance::$update,
    bool,
    bool a1
) {
    bool result = origin(a1);

    auto* player          = this->getLocalPlayer();
    bool  isPlayerInWorld = player && this->isWorldActive();

    static bool s_wasInWorld = false;

    if (isPlayerInWorld) {
        const auto& pos = player->getPosition();
        float       yaw = player->getRotation().y;

        if (!s_wasInWorld) {
            MapDemo::getInstance().getSelf().getLogger().debug("PlayerHook: player entered world");
            MapState::getInstance().resetSmoothCamera(pos.x, pos.z, yaw);
            RegionRenderer::getInstance().clearQueueAndWait();
            MapCacheManager::getInstance().clearAll();
            TerrainScanner::getInstance().clearState();
            s_wasInWorld = true;

            if (config::getConfig().terrain.enableDiskCache) {
                auto worldPath = MapDemo::getInstance().getSelf().getWorldDataDir();
                auto cachePath = worldPath.has_value()
                                   ? worldPath.value() / "terrain_cache"
                                   : MapDemo::getInstance().getSelf().getDataDir() / "terrain_cache";
                std::filesystem::create_directories(cachePath);
                bool cacheOk = MapCacheManager::getInstance().initializeDiskCache(cachePath);
                MapDemo::getInstance().getSelf().getLogger().debug("Terrain disk cache init result: {}", cacheOk);
            }
        }

        MapState::getInstance().updatePlayer(pos.x, pos.y, pos.z, yaw, static_cast<int>(player->getDimensionId()));

        // 地形扫描
        auto& cfg = config::getConfig();
        if (cfg.terrain.enable) {
            auto pChunk = ChunkPos(pos.x, pos.z);
            int  dim    = static_cast<int>(player->getDimensionId());
            TerrainScanner::getInstance().update(this->getRegion(), ChunkPosWithDim{pChunk.x, pChunk.z, dim});

            static int removeTimer  = 1;
            removeTimer            %= 1200;
            if (!removeTimer++) {
                MapCacheManager::getInstance().evictRegionsOutsideRadius(
                    ChunkPosWithDim{pChunk.x, pChunk.z, dim},
                    cfg.terrain.scanRadius
                );
            }
        }
    } else {
        if (s_wasInWorld) {
            MapDemo::getInstance().getSelf().getLogger().debug("PlayerHook: player left world");
            MapState::getInstance().clearPlayer();
            RegionRenderer::getInstance().clearQueueAndWait();
            MapCacheManager::getInstance().clearAll();
            TerrainScanner::getInstance().clearState();
            s_wasInWorld = false;
        }
    }

    return result;
}

} // namespace map_demo
