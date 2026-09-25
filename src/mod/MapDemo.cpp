#include "mod/MapDemo.h"

#include "config/Config.h"
#include "data/cache/WorldMapCacheManager.h"
#include "helper/HookRegistry.h"
#include "helper/InputBlocker.h"
#include "ll/api/Config.h"
#include "ll/api/mod/RegisterHelper.h"
#include "state/TerrainScanner.h"
#include "state/render/RendererManager.h"

namespace map_demo {

MapDemo& MapDemo::getInstance() {
    static MapDemo instance;
    return instance;
}

bool MapDemo::load() {
    const auto& logger = getSelf().getLogger();

    // load config
    try {
        const auto& configFilePath = getSelf().getConfigDir() / "config.json";
        if (!ll::config::loadConfig(config::getConfig(), configFilePath)) {
            logger.warn("Cannot load configurations from {}", configFilePath);
            logger.info("Saving default configurations");
            if (!ll::config::saveConfig(config::getConfig(), configFilePath)) {
                logger.error("Cannot save default configurations to {}", configFilePath);
                return false;
            }
        }
    } catch (const std::exception& e) {
        logger.error("Failed to load config.json. Please check the file!");
        logger.error("{}", e.what());
        return false;
    } catch (...) {
        logger.error("Failed to load config.json. Please check the file!");
        return false;
    }

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
