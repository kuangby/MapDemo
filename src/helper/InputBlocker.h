#pragma once

#include <ll/api/event/ListenerBase.h>

#include <mutex>


class ClientInstance;

namespace map_demo {

// 大地图打开时的输入拦截：
// 通过 ll::event::KeyInputEvent / MouseInputEvent 取消事件，禁用与游戏的交互；
// 同时把鼠标输入记录下来供大地图 UI 使用。
class InputBlocker {
public:
    // 大地图 UI 的鼠标输入快照（事件被拦截前记录，供 WorldMapRenderer 每帧消费）
    struct MouseState {
        float x{0.0f};
        float y{0.0f};
        bool  leftDown{false};
        bool  rightDown{false};
        int   wheelDelta{0}; // 自上次消费以来累积的滚轮量
    };

    static void registerListeners();
    static void unregisterListeners();

    // 由 PlayerHook 在进入/离开世界时设置（用于 releaseMouse/grabMouse）
    static void setClientInstance(ClientInstance* ci);

    // 读取当前鼠标状态并清除累积量（滚轮）
    static MouseState consumeMouseState();

    static void openWorldMap();
    static void closeWorldMap();

private:
    static ll::event::ListenerPtr s_keyListener;
    static ll::event::ListenerPtr s_mouseListener;
    static ClientInstance*        s_clientInstance;

    static std::mutex s_mouseMutex;
    static MouseState s_mouse;
};

} // namespace map_demo
