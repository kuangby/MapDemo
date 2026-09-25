#include "mod/MapDemo.h"

#include "data/cache/WorldMapCacheManager.h"
#include "helper/HookRegistry.h"
#include "helper/InputBlocker.h"
#include "ll/api/mod/RegisterHelper.h"
#include "state/TerrainScanner.h"
#include "state/render/RendererManager.h"

namespace map_demo {

MapDemo& MapDemo::getInstance() {
    static MapDemo instance;
    return instance;
}

bool MapDemo::load() {
    registerAllHooks();
    return true;
}

bool MapDemo::enable() {
    InputBlocker::registerListeners();
    return true;
}

bool MapDemo::disable() {
    InputBlocker::unregisterListeners();
    WorldMapCacheManager::getInstance().shutdown();
    unregisterAllHooks();
    RendererManager::getInstance().shutdown();
    TerrainScanner::getInstance().shutdown();
    return true;
}

} // namespace map_demo

LL_REGISTER_MOD(map_demo::MapDemo, map_demo::MapDemo::getInstance());
