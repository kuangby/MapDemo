#include "mod/MapDemo.h"

#include "config/Config.h"
#include "data/cache/WorldMapCacheManager.h"
#include "helper/HookRegistry.h"
#include "helper/InputBlocker.h"
#include "helper/ShadowDebugLogger.h"
#include "ll/api/mod/RegisterHelper.h"
#include "state/TerrainScanner.h"
#include "state/render/RendererManager.h"

namespace map_demo {

MapDemo& MapDemo::getInstance() {
    static MapDemo instance;
    return instance;
}

bool MapDemo::load() {
    getSelf().getLogger().setLevel(ll::io::LogLevel::Debug);
    getSelf().getLogger().debug("Loading...");

    auto& cfg = config::getConfig();

    ShadowDebugLogger::getInstance().setEnabled(cfg.terrain.shadow.debugLog);

    registerAllHooks();
    getSelf().getLogger().debug("Hooks registered");
    return true;
}

bool MapDemo::enable() {
    getSelf().getLogger().debug("Enabling...");
    InputBlocker::registerListeners();
    return true;
}

bool MapDemo::disable() {
    getSelf().getLogger().debug("Disabling...");
    InputBlocker::unregisterListeners();
    WorldMapCacheManager::getInstance().shutdown();
    unregisterAllHooks();
    RendererManager::getInstance().shutdown();
    TerrainScanner::getInstance().shutdown();
    ShadowDebugLogger::getInstance().shutdown();
    getSelf().getLogger().debug("Hooks unregistered");
    return true;
}

} // namespace map_demo

LL_REGISTER_MOD(map_demo::MapDemo, map_demo::MapDemo::getInstance());
