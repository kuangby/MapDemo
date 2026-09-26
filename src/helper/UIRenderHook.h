#pragma once

#include <ll/api/memory/Hook.h>
#include <mc/client/renderer/screen/MinecraftUIRenderContext.h>

#include <mutex>

#include "helper/DX11Hook.h"

namespace coral_map {

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

    std::call_once(g_initOnce, [] { DX11Hook::init(); });
}

} // namespace coral_map
