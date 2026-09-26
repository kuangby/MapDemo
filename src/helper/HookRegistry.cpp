#include "helper/HookRegistry.h"

#include "helper/DX11Hook.h"
#include "helper/PlayerHook.h"
#include "helper/UIRenderHook.h"

namespace coral_map {

void registerAllHooks() {
    ClientInstanceUpdateHook::hook();
    UIRenderContextFlushTextHook::hook();
}

void unregisterAllHooks() {
    ClientInstanceUpdateHook::unhook();
    UIRenderContextFlushTextHook::unhook();
    DX11Hook::shutdown();
}

} // namespace coral_map
