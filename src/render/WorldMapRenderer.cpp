#include "render/WorldMapRenderer.h"

#include "config/Config.h"
#include "data/cache/WorldMapCacheManager.h"
#include "helper/InputBlocker.h"
#include "state/MapState.h"

#include <imgui.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>


namespace map_demo {

namespace {

// 点采样/线性采样状态：放大（zoom>=1，一纹素占多像素）用点采样保持方块锐利，
// 缩小（zoom<1，多纹素压到一像素）用线性采样抗锯齿
ID3D11SamplerState* g_pointSampler  = nullptr;
ID3D11SamplerState* g_linearSampler = nullptr;

void ensureSamplers() {
    if (g_pointSampler && g_linearSampler) return;
    auto* device = DX11Hook::getDevice();
    if (!device) return;

    D3D11_SAMPLER_DESC desc = {};
    desc.AddressU           = D3D11_TEXTURE_ADDRESS_CLAMP;
    desc.AddressV           = D3D11_TEXTURE_ADDRESS_CLAMP;
    desc.AddressW           = D3D11_TEXTURE_ADDRESS_CLAMP;

    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    device->CreateSamplerState(&desc, &g_pointSampler);

    // 与 ImGui DX11 后端默认采样器保持一致（linear + wrap），用于绘制结束后还原
    desc.Filter   = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    device->CreateSamplerState(&desc, &g_linearSampler);
}

void setSamplerCallback(const ImDrawList* /*drawList*/, const ImDrawCmd* cmd) {
    auto* context = DX11Hook::getContext();
    if (!context || !cmd->UserCallbackData) return;
    auto* sampler = static_cast<ID3D11SamplerState*>(cmd->UserCallbackData);
    context->PSSetSamplers(0, 1, &sampler);
}

} // namespace

WorldMapRenderer& WorldMapRenderer::getInstance() {
    static WorldMapRenderer instance;
    return instance;
}

void WorldMapRenderer::requestClearTextures() { clearRequested_ = true; }

void WorldMapRenderer::releaseTexture(RegionTexture& rt) {
    if (rt.srv) {
        rt.srv->Release();
        rt.srv = nullptr;
    }
    if (rt.tex) {
        rt.tex->Release();
        rt.tex = nullptr;
    }
}

void WorldMapRenderer::garbageCollectTextures() {
    auto& cfg = config::getConfig().worldMap;
    for (auto it = textures_.begin(); it != textures_.end();) {
        if (frameCounter_ - it->second.lastUsedFrame > cfg.textureIdleFrames) {
            releaseTexture(it->second);
            it = textures_.erase(it);
        } else {
            ++it;
        }
    }
}

WorldMapRenderer::RegionTexture* WorldMapRenderer::ensureTexture(const RegionPos& pos, int& createdThisFrame) {
    auto [it, inserted] = textures_.try_emplace(pos);
    auto& rt            = it->second;
    rt.lastUsedFrame    = frameCounter_;

    auto* device  = DX11Hook::getDevice();
    auto* context = DX11Hook::getContext();
    if (!device || !context) return nullptr;

    // 纹理已存在时才无条件取更新；纹理不存在且超出每帧新建预算时，留到下一帧再取
    if (!rt.tex && createdThisFrame >= config::getConfig().worldMap.maxNewTexturesPerFrame) return nullptr;

    static thread_local std::array<std::uint8_t, WorldMapRegionData::kDataSize> buf;
    auto result = WorldMapCacheManager::getInstance().fetchForRender(pos, buf);
    if (result == WorldMapCacheManager::FetchResult::NotLoaded) return nullptr;
    if (result == WorldMapCacheManager::FetchResult::NoChange) return rt.srv ? &rt : nullptr;

    // Updated：创建或更新纹理
    if (!rt.tex) {
        D3D11_TEXTURE2D_DESC desc   = {};
        desc.Width                  = WorldMapRegionData::kSize;
        desc.Height                 = WorldMapRegionData::kSize;
        desc.MipLevels              = 1;
        desc.ArraySize              = 1;
        desc.Format                 = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count       = 1;
        desc.Usage                  = D3D11_USAGE_DEFAULT;
        desc.BindFlags              = D3D11_BIND_SHADER_RESOURCE;

        D3D11_SUBRESOURCE_DATA initData = {};
        initData.pSysMem                = buf.data();
        initData.SysMemPitch            = WorldMapRegionData::kSize * 4;

        if (FAILED(device->CreateTexture2D(&desc, &initData, &rt.tex))) return nullptr;
        if (FAILED(device->CreateShaderResourceView(rt.tex, nullptr, &rt.srv))) {
            releaseTexture(rt);
            return nullptr;
        }
        ++createdThisFrame;
    } else {
        context->UpdateSubresource(rt.tex, 0, nullptr, buf.data(), WorldMapRegionData::kSize * 4, 0);
    }
    return &rt;
}

void WorldMapRenderer::handleInput(double& centerX, double& centerZ, float zoom, float screenW, float screenH) {
    auto& state = MapState::getInstance();
    auto& cfg   = config::getConfig().worldMap;
    auto  mouse = InputBlocker::consumeMouseState();

    // 左键拖拽平移
    if (mouse.leftDown && prevLeftDown_) {
        state.worldMapOffsetX -= (mouse.x - prevMouseX_) / zoom;
        state.worldMapOffsetZ -= (mouse.y - prevMouseY_) / zoom;
    }

    // 滚轮缩放：以玩家箭头位置（世界坐标即平滑相机目标点）为中心
    if (mouse.wheelDelta != 0) {
        float newZoom = std::clamp(
            zoom * std::pow(cfg.zoomStep, static_cast<float>(mouse.wheelDelta)),
            cfg.minZoom,
            cfg.maxZoom
        );
        if (newZoom != zoom) {
            double anchorX = state.smoothX();
            double anchorZ = state.smoothZ();
            // 箭头当前屏幕位置
            double arrowSX = (anchorX - centerX) * zoom + screenW * 0.5;
            double arrowSZ = (anchorZ - centerZ) * zoom + screenH * 0.5;
            // 缩放后箭头仍停留在原屏幕位置
            centerX = anchorX - (arrowSX - screenW * 0.5) / newZoom;
            centerZ = anchorZ - (arrowSZ - screenH * 0.5) / newZoom;
            state.worldMapOffsetX = static_cast<float>(centerX - anchorX);
            state.worldMapOffsetZ = static_cast<float>(centerZ - anchorZ);
            state.worldMapZoom    = newZoom;
        }
    }

    prevMouseX_   = mouse.x;
    prevMouseY_   = mouse.y;
    prevLeftDown_ = mouse.leftDown;
}

void WorldMapRenderer::render() {
    auto& state = MapState::getInstance();
    if (!state.showWorldMap) {
        prevLeftDown_ = false;
        return;
    }

    ++frameCounter_;

    if (clearRequested_.exchange(false)) {
        for (auto& [pos, rt] : textures_) releaseTexture(rt);
        textures_.clear();
    }
    if (frameCounter_ % 300 == 0) garbageCollectTextures();

    auto&       io       = ImGui::GetIO();
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    float       screenW  = io.DisplaySize.x;
    float       screenH  = io.DisplaySize.y;
    auto&       cfg      = config::getConfig().worldMap;

    // 全屏背景（不透明，盖住先绘制的小地图）
    drawList->AddRectFilled(
        ImVec2(0.0f, 0.0f),
        ImVec2(screenW, screenH),
        IM_COL32(16, 16, 20, static_cast<int>(255.0f * cfg.backgroundAlpha))
    );

    float  zoom    = std::clamp(state.worldMapZoom, cfg.minZoom, cfg.maxZoom);
    double centerX = static_cast<double>(state.smoothX()) + state.worldMapOffsetX;
    double centerZ = static_cast<double>(state.smoothZ()) + state.worldMapOffsetZ;

    handleInput(centerX, centerZ, zoom, screenW, screenH);
    zoom = state.worldMapZoom;

    auto worldToScreen = [&](double wx, double wz) -> ImVec2 {
        return ImVec2(
            static_cast<float>((wx - centerX) * zoom + screenW * 0.5),
            static_cast<float>((wz - centerZ) * zoom + screenH * 0.5)
        );
    };

    // 可见 region 范围
    double minX = centerX - screenW * 0.5 / zoom;
    double maxX = centerX + screenW * 0.5 / zoom;
    double minZ = centerZ - screenH * 0.5 / zoom;
    double maxZ = centerZ + screenH * 0.5 / zoom;
    int    rx0  = static_cast<int>(std::floor(minX / WorldMapRegionData::kSize));
    int    rx1  = static_cast<int>(std::floor(maxX / WorldMapRegionData::kSize));
    int    rz0  = static_cast<int>(std::floor(minZ / WorldMapRegionData::kSize));
    int    rz1  = static_cast<int>(std::floor(maxZ / WorldMapRegionData::kSize));

    int createdThisFrame = 0;
    ensureSamplers();
    bool pointSampling = zoom >= 1.0f;
    if (g_pointSampler && g_linearSampler) {
        drawList->AddCallback(
            setSamplerCallback,
            pointSampling ? static_cast<void*>(g_pointSampler) : static_cast<void*>(g_linearSampler)
        );
    }
    for (int rz = rz0; rz <= rz1; ++rz) {
        for (int rx = rx0; rx <= rx1; ++rx) {
            RegionPos pos(rx, rz, state.dimensionId());
            ImVec2    p0 = worldToScreen(static_cast<double>(rx) * WorldMapRegionData::kSize,
                                         static_cast<double>(rz) * WorldMapRegionData::kSize);
            ImVec2    p1 = worldToScreen(static_cast<double>(rx + 1) * WorldMapRegionData::kSize,
                                         static_cast<double>(rz + 1) * WorldMapRegionData::kSize);
            // 屏幕坐标取整，防止相邻图块间出现亚像素缝隙抖动
            p0.x = std::floor(p0.x);
            p0.y = std::floor(p0.y);
            p1.x = std::floor(p1.x);
            p1.y = std::floor(p1.y);

            // ensureTexture 内部会触发磁盘加载排队；无数据时画占位底色
            if (auto* rt = ensureTexture(pos, createdThisFrame); rt && rt->srv) {
                drawList->AddImage(ImTextureRef(static_cast<ImTextureID>(reinterpret_cast<intptr_t>(rt->srv))), p0, p1);
            } else {
                drawList->AddRectFilled(p0, p1, IM_COL32(28, 28, 34, 255));
            }
        }
    }
    // 还原为 ImGui 默认线性采样，避免影响后续文字/箭头绘制
    if (pointSampling && g_linearSampler) {
        drawList->AddCallback(setSamplerCallback, static_cast<void*>(g_linearSampler));
    }

    // 玩家位置与朝向（与小地图相同的旋转约定：yaw=0 朝 -z 即屏幕上方）
    if (state.hasPlayer()) {
        ImVec2 pp    = worldToScreen(state.smoothX(), state.smoothZ());
        float  yawRad = state.renderYawRad();
        float  cosY   = std::cos(yawRad);
        float  sinY   = std::sin(yawRad);
        auto   rotate = [&](float x, float z) {
            return ImVec2(pp.x + (x * cosY - z * sinY), pp.y + (x * sinY + z * cosY));
        };
        drawList->AddTriangleFilled(
            rotate(0.0f, -12.0f),
            rotate(-7.0f, 12.0f),
            rotate(7.0f, 12.0f),
            IM_COL32(0, 0, 0, 255)
        );
        drawList->AddTriangleFilled(
            rotate(0.0f, -9.0f),
            rotate(-5.0f, 12.0f),
            rotate(5.0f, 12.0f),
            IM_COL32(220, 50, 50, 255)
        );
    }

    // 底部坐标与缩放信息
    if (state.hasPlayer()) {
        char text[96];
        std::snprintf(
            text,
            sizeof(text),
            "X: %d  Z: %d   缩放: %.2fx",
            state.player().blockX(),
            state.player().blockZ(),
            static_cast<double>(zoom)
        );
        ImVec2 textSize = ImGui::CalcTextSize(text);
        ImVec2 textPos((screenW - textSize.x) * 0.5f, screenH - textSize.y - 10.0f);
        drawList->AddText(ImVec2(textPos.x + 1.0f, textPos.y + 1.0f), IM_COL32(0, 0, 0, 200), text);
        drawList->AddText(textPos, IM_COL32(255, 255, 255, 255), text);
    }
}

} // namespace map_demo
