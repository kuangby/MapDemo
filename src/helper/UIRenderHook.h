#pragma once

#include <ll/api/memory/Hook.h>
#include <mc/client/renderer/screen/MinecraftUIRenderContext.h>

#include <mutex>

#include "helper/DX11Hook.h"
#include "mod/MapDemo.h"

namespace map_demo {

inline std::once_flag g_initOnce;

LL_TYPE_INSTANCE_HOOK(
    UIRenderContextFlushTextHook,
    ll::memory::HookPriority::Normal,
    MinecraftUIRenderContext,
    &MinecraftUIRenderContext::$flushText,
    void,
    float deltaTime,
    std::optional<float> obfuscateSwitchTime
) {
    origin(deltaTime, obfuscateSwitchTime);

    std::call_once(g_initOnce, [] {
        MapDemo::getInstance().getSelf().getLogger().debug("UIRenderContextFlushTextHook: initializing DX11Hook");
        bool ok = DX11Hook::init();
        MapDemo::getInstance().getSelf().getLogger().debug("UIRenderContextFlushTextHook: DX11Hook init = {}", ok);
    });
}

} // namespace map_demo
