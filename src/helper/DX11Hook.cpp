#include "helper/DX11Hook.h"

#include "config/Config.h"
#include "mod/MapDemo.h"
#include "render/MiniMapRenderer.h"

#include <backends/imgui_impl_dx11.h>
#include <imgui.h>

#include "ll/api/memory/Hook.h"

#include <atomic>
#include <chrono>

namespace map_demo::DX11Hook {

namespace {

using Present_t = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT);

Present_t oPresent = nullptr;

ll::memory::FuncPtr g_targetPresent = nullptr;
ll::memory::FuncPtr g_detourPresent = nullptr;

ID3D11Device*        g_pd3dDevice        = nullptr;
ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
HWND                 g_hWnd              = nullptr;
std::atomic<bool>    g_initialized{false};

void shutdownImGui() {
    if (g_initialized) {
        ImGui_ImplDX11_Shutdown();
        ImGui::DestroyContext();
        g_initialized = false;
    }
}

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
    static bool s_presentLogged = false;
    if (!s_presentLogged) {
        MapDemo::getInstance().getSelf().getLogger().debug("hkPresent: first call");
        s_presentLogged = true;
    }

    if (!g_initialized) {
        HRESULT hr = pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_pd3dDevice);
        if (SUCCEEDED(hr)) {
            g_pd3dDevice->GetImmediateContext(&g_pd3dDeviceContext);

            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            g_hWnd = sd.OutputWindow;
            if (!g_hWnd) g_hWnd = FindWindowW(L"Minecraft", NULL);

            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.Fonts->AddFontFromFileTTF(
                "c:\\Windows\\Fonts\\msyh.ttc",
                config::getConfig().fontSize,
                NULL,
                io.Fonts->GetGlyphRangesChineseFull()
            );

            ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

            g_initialized = true;
            MapDemo::getInstance().getSelf().getLogger().debug("hkPresent: ImGui initialized");
        } else {
            MapDemo::getInstance().getSelf().getLogger().debug("hkPresent: GetDevice failed, hr={:X}", hr);
        }
    }

    if (g_initialized && g_pd3dDeviceContext) {
        ID3D11Texture2D* pBackBuffer = nullptr;
        if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer))) {
            ID3D11RenderTargetView* rtv = nullptr;
            g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &rtv);
            pBackBuffer->Release();

            if (rtv) {
                g_pd3dDeviceContext->OMSetRenderTargets(1, &rtv, NULL);

                ImGuiIO& io = ImGui::GetIO();

                if (g_hWnd) {
                    RECT rect;
                    if (GetClientRect(g_hWnd, &rect)) {
                        io.DisplaySize = ImVec2(
                            static_cast<float>(rect.right - rect.left),
                            static_cast<float>(rect.bottom - rect.top)
                        );
                    }
                }

                static auto s_lastFrameTime = std::chrono::steady_clock::now();
                auto now = std::chrono::steady_clock::now();
                float dt = std::chrono::duration<float>(now - s_lastFrameTime).count();
                s_lastFrameTime = now;
                io.DeltaTime = dt > 0.0f ? dt : 1.0f / 60.0f;

                ImGui_ImplDX11_NewFrame();
                ImGui::NewFrame();

                MiniMapRenderer::getInstance().render();

                ImGui::Render();
                ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

                ID3D11RenderTargetView* nullRTV = nullptr;
                g_pd3dDeviceContext->OMSetRenderTargets(1, &nullRTV, NULL);
                rtv->Release();
                g_pd3dDeviceContext->ClearState();
                g_pd3dDeviceContext->Flush();
            }
        }
    }

    return oPresent(pSwapChain, SyncInterval, Flags);
}

} // namespace

bool init() {
    MapDemo::getInstance().getSelf().getLogger().debug("DX11Hook::init: start");
    HWND hwnd = FindWindowW(L"Minecraft", NULL);
    if (!hwnd) hwnd = GetForegroundWindow();
    MapDemo::getInstance().getSelf().getLogger().debug("DX11Hook::init: hwnd = {}", (void*)hwnd);
    if (!hwnd) return false;

    D3D_FEATURE_LEVEL    featureLevel = D3D_FEATURE_LEVEL_11_0;
    DXGI_SWAP_CHAIN_DESC sd           = {};
    sd.BufferCount                    = 1;
    sd.BufferDesc.Format              = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage                    = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow                   = hwnd;
    sd.SampleDesc.Count               = 1;
    sd.Windowed                       = TRUE;
    sd.SwapEffect                     = DXGI_SWAP_EFFECT_DISCARD;

    ID3D11Device*        dummyDevice    = nullptr;
    IDXGISwapChain*      dummySwapChain = nullptr;
    ID3D11DeviceContext* dummyContext   = nullptr;

    if (SUCCEEDED(D3D11CreateDeviceAndSwapChain(
            NULL,
            D3D_DRIVER_TYPE_HARDWARE,
            NULL,
            0,
            &featureLevel,
            1,
            D3D11_SDK_VERSION,
            &sd,
            &dummySwapChain,
            &dummyDevice,
            NULL,
            &dummyContext
        ))) {
        MapDemo::getInstance().getSelf().getLogger().debug("DX11Hook::init: dummy swapchain created");
        void** pVTable = *reinterpret_cast<void***>(dummySwapChain);

        Present_t presentPtr = reinterpret_cast<Present_t>(pVTable[8]);
        g_targetPresent      = ll::memory::toFuncPtr(presentPtr);
        g_detourPresent      = ll::memory::toFuncPtr(&hkPresent);
        int presentHookResult = ll::memory::hook(
            g_targetPresent,
            g_detourPresent,
            reinterpret_cast<ll::memory::FuncPtr*>(&oPresent),
            ll::memory::HookPriority::Normal
        );
        MapDemo::getInstance().getSelf().getLogger().debug("DX11Hook::init: Present hook result = {}", presentHookResult);

        dummySwapChain->Release();
        dummyDevice->Release();
        dummyContext->Release();
        MapDemo::getInstance().getSelf().getLogger().debug("DX11Hook::init: Present hook installed");
        return true;
    }

    MapDemo::getInstance().getSelf().getLogger().debug("DX11Hook::init: failed to create dummy swapchain");
    return false;
}

void shutdown() {
    if (g_targetPresent && g_detourPresent) {
        ll::memory::unhook(g_targetPresent, g_detourPresent);
    }
    shutdownImGui();
    if (g_pd3dDeviceContext) {
        g_pd3dDeviceContext->Release();
        g_pd3dDeviceContext = nullptr;
    }
    if (g_pd3dDevice) {
        g_pd3dDevice->Release();
        g_pd3dDevice = nullptr;
    }
    g_hWnd = nullptr;
}

} // namespace map_demo::DX11Hook
