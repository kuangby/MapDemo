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


#include "BlockChangeListener.h"
#include "config/Config.h"
#include "data/cache/MapCacheManager.h"
#include "data/cache/WorldMapCacheManager.h"
#include "helper/DX11Hook.h"
#include "helper/InputBlocker.h"
#include "mod/MapDemo.h"
#include "render/WorldMapRenderer.h"
#include "state/MapState.h"
#include "state/TerrainScanner.h"
#include "state/render/RendererManager.h"


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

    static int dimId = -1;

    static BlockSource* s_listenerSource = nullptr;

    if (isPlayerInWorld) {
        const auto& pos         = player->getPosition();
        float       yaw         = player->getRotation().y;
        int         playerDimId = player->getDimensionId();

        if (!s_wasInWorld) {
            MapState::getInstance().resetSmoothCamera(pos.x, pos.z, yaw);
            RendererManager::getInstance().clearQueueAndWait();
            MapCacheManager::getInstance().clearAll();
            TerrainScanner::getInstance().clearState();
            s_wasInWorld = true;
            dimId        = playerDimId;

            InputBlocker::setClientInstance(this);

            s_listenerSource = &player->getDimensionBlockSource();
            s_listenerSource->addListener(BlockChangeListener::getInstance());

            if (config::getConfig().terrain.enableDiskCache) {
                auto worldPath = MapDemo::getInstance().getSelf().getWorldDataDir();
                auto cachePath = worldPath.has_value()
                                   ? worldPath.value() / "terrain_cache"
                                   : MapDemo::getInstance().getSelf().getDataDir() / "terrain_cache";
                std::filesystem::create_directories(cachePath);
                MapCacheManager::getInstance().initializeDiskCache(cachePath);

                // 大地图缓存：本地存档存 getWorldDataDir，远程服务器按 ip+端口+种子 存 getDataDir/servers 下
                WorldMapCacheManager::getInstance().onEnterWorld(this, player);
            }
        } else if (playerDimId != dimId) {
            dimId = playerDimId;
            MapState::getInstance().resetSmoothCamera(pos.x, pos.z, yaw);
            RendererManager::getInstance().clearQueueAndWait();
            MapCacheManager::getInstance().clearAll();
            TerrainScanner::getInstance().clearState();

            if (s_listenerSource) s_listenerSource->removeListener(BlockChangeListener::getInstance());
            s_listenerSource = &player->getDimensionBlockSource();
            s_listenerSource->addListener(BlockChangeListener::getInstance());
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

        // 大地图打开期间渲染线程每帧 ClipCursor(nullptr) 解除锁定；而游戏抓取鼠标时
        // 只是每帧把光标回中，快速转视角时光标可能在一帧内漂出窗口（此时点击会切走焦点）。
        // 参考 ChiyanMap：抓取状态（光标隐藏）下把光标钳制在客户区中心 2x2 死区内
        if (!MapState::getInstance().showWorldMap) {
            if (HWND hwnd = DX11Hook::getHwnd(); hwnd && GetForegroundWindow() == hwnd) {
                CURSORINFO ci{sizeof(CURSORINFO)};
                if (GetCursorInfo(&ci)) {
                    if (ci.flags == 0) {
                        RECT clientRect;
                        GetClientRect(hwnd, &clientRect);
                        POINT ptCenter{
                            (clientRect.right - clientRect.left) / 2,
                            (clientRect.bottom - clientRect.top) / 2
                        };
                        ClientToScreen(hwnd, &ptCenter);
                        RECT centerRect{ptCenter.x - 1, ptCenter.y - 1, ptCenter.x + 1, ptCenter.y + 1};
                        ClipCursor(&centerRect);
                    } else {
                        // 背包/暂停菜单等原生 UI 状态（系统光标可见），放开钳制
                        ClipCursor(nullptr);
                    }
                }
            }
        }
    } else {
        if (s_wasInWorld) {
            if (s_listenerSource) {
                s_listenerSource->removeListener(BlockChangeListener::getInstance());
                s_listenerSource = nullptr;
            }
            if (MapState::getInstance().showWorldMap) InputBlocker::closeWorldMap();
            WorldMapCacheManager::getInstance().onLeaveWorld();
            WorldMapRenderer::getInstance().requestClearTextures();
            InputBlocker::setClientInstance(nullptr);
            MapState::getInstance().clearPlayer();
            RendererManager::getInstance().clearQueueAndWait();
            MapCacheManager::getInstance().clearAll();
            TerrainScanner::getInstance().clearState();
            s_wasInWorld = false;
        }
    }

    return result;
}

} // namespace map_demo
