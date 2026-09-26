#include "mod/CoralMap.h"

#include "config/Config.h"
#include "data/cache/WorldMapCacheManager.h"
#include "helper/HookRegistry.h"
#include "helper/InputBlocker.h"
#include "ll/api/Config.h"
#include "ll/api/mod/RegisterHelper.h"
#include "state/BiomeColorMap.h"
#include "state/TerrainScanner.h"
#include "state/render/RendererManager.h"

namespace coral_map {

CoralMap& CoralMap::getInstance() {
    static CoralMap instance;
    return instance;
}

bool CoralMap::load() {
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

    // load biome color table (void base colors); 失败时回退到游戏内群系采样
    const auto& biomeColorPath = getSelf().getModDir() / "resource" / "biome_color.json";
    if (!BiomeColorMap::getInstance().load(biomeColorPath)) {
        logger.warn("Cannot load biome colors from {}, falling back to in-game biome sampling", biomeColorPath);
    }

    registerAllHooks();
    return true;
}

bool CoralMap::enable() {
    InputBlocker::registerListeners();
    return true;
}

bool CoralMap::disable() {
    InputBlocker::unregisterListeners();
    // 先摘 hook：渲染线程不再进入本 mod 代码，DX11Hook::shutdown 内会等 in-flight 帧退出
    unregisterAllHooks();
    // 再停 bake 工作线程：hook 已摘，不会再有新任务入队，join 有界
    RendererManager::getInstance().shutdown();
    // 最后停缓存：同步刷盘期间已无任何线程访问缓存
    WorldMapCacheManager::getInstance().shutdown();
    TerrainScanner::getInstance().shutdown();
    return true;
}

} // namespace coral_map

LL_REGISTER_MOD(coral_map::CoralMap, coral_map::CoralMap::getInstance());
