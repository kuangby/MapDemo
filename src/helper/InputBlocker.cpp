#include "helper/InputBlocker.h"

#include "config/Config.h"
#include "mod/MapDemo.h"
#include "state/MapState.h"

#include <ll/api/event/EventBus.h>
#include <ll/api/event/input/KeyInputEvent.h>
#include <ll/api/event/input/MouseInputEvent.h>
#include <mc/client/game/ClientInstance.h>


namespace map_demo {

ll::event::ListenerPtr InputBlocker::s_keyListener;
ll::event::ListenerPtr InputBlocker::s_mouseListener;
ClientInstance*        InputBlocker::s_clientInstance = nullptr;
std::mutex             InputBlocker::s_mouseMutex;
InputBlocker::MouseState InputBlocker::s_mouse;

namespace {
constexpr int kEscapeKey = 0x1B; // VK_ESCAPE
}

void InputBlocker::registerListeners() {
    auto& bus = ll::event::EventBus::getInstance();

    s_keyListener = bus.emplaceListener<ll::event::KeyInputEvent>([](ll::event::KeyInputEvent& event) {
        auto& state     = MapState::getInstance();
        int   keyCode   = event.keyCode();
        bool  isDown    = event.isDown();
        int   toggleKey = config::getConfig().worldMap.toggleKey;

        if (!state.showWorldMap) {
            if (keyCode == toggleKey) {
                // 仅在游戏捕获鼠标（即不在聊天栏/其他 UI）时响应，避免打字时触发
                bool mouseGrabbed = s_clientInstance && s_clientInstance->getMouseGrabbed();
                if (isDown && mouseGrabbed) {
                    event.cancel();
                    openWorldMap();
                }
            }
            return;
        }
        // 大地图打开：拦截一切按键
        event.cancel();
        if (isDown && (keyCode == toggleKey || keyCode == kEscapeKey)) closeWorldMap();
    });

    s_mouseListener = bus.emplaceListener<ll::event::MouseInputEvent>([](ll::event::MouseInputEvent& event) {
        auto& state = MapState::getInstance();
        if (!state.showWorldMap) return;

        {
            std::lock_guard<std::mutex> lock(s_mouseMutex);
            s_mouse.x       = static_cast<float>(event.x());
            s_mouse.y       = static_cast<float>(event.y());
            char buttonId   = event.actionButtonId();
            char buttonData = event.buttonData();
            // MC 约定：1=左键 2=右键 3=中键 4=滚轮；buttonData 非 0 表示按下，滚轮时为滚动方向
            switch (buttonId) {
            case 1:
                s_mouse.leftDown = buttonData != 0;
                break;
            case 2:
                s_mouse.rightDown = buttonData != 0;
                break;
            case 4:
                // 滚轮 buttonData 可能是 ±120 一类的绝对量，归一化为方向，避免缩放一步到顶
                s_mouse.wheelDelta += (buttonData > 0) ? 1 : ((buttonData < 0) ? -1 : 0);
                break;
            default:
                break;
            }
        }
        event.cancel();
    });

    MapDemo::getInstance().getSelf().getLogger().debug("InputBlocker: listeners registered");
}

void InputBlocker::unregisterListeners() {
    auto& bus = ll::event::EventBus::getInstance();
    if (s_keyListener) {
        bus.removeListener<ll::event::KeyInputEvent>(s_keyListener);
        s_keyListener = nullptr;
    }
    if (s_mouseListener) {
        bus.removeListener<ll::event::MouseInputEvent>(s_mouseListener);
        s_mouseListener = nullptr;
    }
}

void InputBlocker::setClientInstance(ClientInstance* ci) { s_clientInstance = ci; }

InputBlocker::MouseState InputBlocker::consumeMouseState() {
    std::lock_guard<std::mutex> lock(s_mouseMutex);
    MouseState                  snapshot = s_mouse;
    s_mouse.wheelDelta                   = 0;
    return snapshot;
}

void InputBlocker::openWorldMap() {
    auto& state           = MapState::getInstance();
    state.showWorldMap    = true;
    state.worldMapOffsetX = 0.0f; // 以玩家为中心
    state.worldMapOffsetZ = 0.0f;
    {
        std::lock_guard<std::mutex> lock(s_mouseMutex);
        s_mouse = MouseState{};
    }
    if (s_clientInstance) s_clientInstance->releaseMouse();
}

void InputBlocker::closeWorldMap() {
    MapState::getInstance().showWorldMap = false;
    if (s_clientInstance) s_clientInstance->grabMouse();
}

} // namespace map_demo
