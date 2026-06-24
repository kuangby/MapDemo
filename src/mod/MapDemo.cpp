#include "mod/MapDemo.h"

#include "helper/HookRegistry.h"
#include "ll/api/mod/RegisterHelper.h"

namespace map_demo {

MapDemo& MapDemo::getInstance() {
    static MapDemo instance;
    return instance;
}

bool MapDemo::load() {
    getSelf().getLogger().setLevel(ll::io::LogLevel::Debug);
    getSelf().getLogger().debug("Loading...");
    registerAllHooks();
    getSelf().getLogger().debug("Hooks registered");
    return true;
}

bool MapDemo::enable() {
    getSelf().getLogger().debug("Enabling...");
    return true;
}

bool MapDemo::disable() {
    getSelf().getLogger().debug("Disabling...");
    unregisterAllHooks();
    getSelf().getLogger().debug("Hooks unregistered");
    return true;
}

} // namespace map_demo

LL_REGISTER_MOD(map_demo::MapDemo, map_demo::MapDemo::getInstance());
