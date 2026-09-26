#pragma once

#include "data/pos/RegionPos.h"
#include "helper/DX11Hook.h"

#include <atomic>
#include <unordered_map>


namespace coral_map {

// 大地图渲染器：以 region（256x256 方块）为单位，一张纹理一张图块，ImGui AddImage 拼贴
class WorldMapRenderer {
public:
    static WorldMapRenderer& getInstance();

    // 每帧由 DX11Hook 的 renderImGuiFrame 调用（渲染线程）
    void render();

    // 请求清空全部纹理（主线程在世界切换时调用，实际清理由渲染线程执行）
    void requestClearTextures();

private:
    WorldMapRenderer() = default;

    struct RegionTexture {
        ID3D11Texture2D*          tex = nullptr;
        ID3D11ShaderResourceView* srv = nullptr;
        int                       lastUsedFrame = 0;
    };

    // 获取/更新 region 纹理；返回 nullptr 表示暂无数据（画占位底色）
    RegionTexture* ensureTexture(const RegionPos& pos, int& createdThisFrame);
    void           releaseTexture(RegionTexture& rt);
    void           garbageCollectTextures();
    void           handleInput(float zoom);

    std::unordered_map<RegionPos, RegionTexture> textures_;
    int                                          frameCounter_ = 0;
    std::atomic<bool>                            clearRequested_{false};

    // 上一帧鼠标状态（拖拽用）
    float prevMouseX_    = 0.0f;
    float prevMouseY_    = 0.0f;
    bool  prevLeftDown_  = false;
    // 大地图上一帧是否打开（关闭瞬间复位 ImGui 光标绘制状态用）
    bool  wasOpen_       = false;
};

} // namespace coral_map
