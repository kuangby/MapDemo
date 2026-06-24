#include "helper/HookRegistry.h"

#include "helper/DX11Hook.h"
#include "helper/PlayerHook.h"
#include "helper/UIRenderHook.h"
#include "mod/MapDemo.h"

namespace map_demo {

void registerAllHooks() {
    MapDemo::getInstance().getSelf().getLogger().debug("registerAllHooks: start");
    ClientInstanceUpdateHook::hook();
    MapDemo::getInstance().getSelf().getLogger().debug("registerAllHooks: PlayerHook done");
    UIRenderContextFlushTextHook::hook();
    MapDemo::getInstance().getSelf().getLogger().debug("registerAllHooks: UIRenderHook done");
}

void unregisterAllHooks() {
    MapDemo::getInstance().getSelf().getLogger().debug("unregisterAllHooks: start");
    ClientInstanceUpdateHook::unhook();
    UIRenderContextFlushTextHook::unhook();
    DX11Hook::shutdown();
    MapDemo::getInstance().getSelf().getLogger().debug("unregisterAllHooks: done");
}

} // namespace map_demo
