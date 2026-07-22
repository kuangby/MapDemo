#include "mod/MapDemo.h"

#include "config/Config.h"
#include "helper/HookRegistry.h"
#include "ll/api/mod/RegisterHelper.h"
#include "state/BlockColorManager.h"
#include "state/TerrainScanner.h"
#include "state/render/RendererManager.h"


#include <filesystem>

namespace map_demo {

MapDemo& MapDemo::getInstance() {
    static MapDemo instance;
    return instance;
}

bool MapDemo::load() {
    getSelf().getLogger().setLevel(ll::io::LogLevel::Debug);
    getSelf().getLogger().debug("Loading...");

    auto& cfg            = config::getConfig();
    auto  modDir         = std::filesystem::path(getSelf().getModDir());
    auto  blockColorPath = (modDir / cfg.terrain.blockColorPath).string();
    auto  biomeColorPath = (modDir / cfg.terrain.biomeColorPath).string();

    bool loaded = BlockColorManager::getInstance().loadFromFiles(blockColorPath, biomeColorPath);
    getSelf().getLogger().debug("Block colors load result: {}", loaded);

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
    RendererManager::getInstance().shutdown();
    TerrainScanner::getInstance().shutdown();
    getSelf().getLogger().debug("Hooks unregistered");
    return true;
}

} // namespace map_demo

LL_REGISTER_MOD(map_demo::MapDemo, map_demo::MapDemo::getInstance());
