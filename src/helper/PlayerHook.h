#pragma once

#include <ll/api/memory/Hook.h>
#include <mc/client/game/ClientInstance.h>
#include <mc/client/player/LocalPlayer.h>

#include "mod/MapDemo.h"
#include "state/MapState.h"

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

    auto* player = this->getLocalPlayer();
    if (player && this->isWorldActive()) {
        static bool s_playerLogged = false;
        if (!s_playerLogged) {
            MapDemo::getInstance().getSelf().getLogger().debug("PlayerHook: player found");
            s_playerLogged = true;
        }
        const auto& pos = player->getPosition();
        float yaw = player->getRotation().y;
        MapState::getInstance().updatePlayer(pos.x, pos.y, pos.z, yaw);
    } else {
        static bool s_noPlayerLogged = false;
        if (!s_noPlayerLogged) {
            MapDemo::getInstance().getSelf().getLogger().debug("PlayerHook: no local player yet");
            s_noPlayerLogged = true;
        }
    }

    return result;
}

} // namespace map_demo
