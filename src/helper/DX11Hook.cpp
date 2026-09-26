#include "helper/DX11Hook.h"

#include "config/Config.h"
#include "render/MiniMapRenderer.h"
#include "render/WorldMapRenderer.h"
#include "state/MapState.h"

#include <backends/imgui_impl_dx11.h>
#include <imgui.h>

#include "ll/api/memory/Hook.h"

#include <atomic>
#include <chrono>

namespace coral_map::DX11Hook {

namespace {

using Present_t             = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT);
using Present1_t            = HRESULT(__stdcall*)(IDXGISwapChain1*, UINT, UINT, const DXGI_PRESENT_PARAMETERS*);
using ResizeBuffers_t       = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);
using ExecuteCommandLists_t = void(__stdcall*)(ID3D12CommandQueue*, UINT, ID3D12CommandList* const*);

Present_t             oPresent             = nullptr;
Present1_t            oPresent1            = nullptr;
ResizeBuffers_t       oResizeBuffers       = nullptr;
ExecuteCommandLists_t oExecuteCommandLists = nullptr;

ll::memory::FuncPtr g_targetPresent             = nullptr;
ll::memory::FuncPtr g_detourPresent             = nullptr;
ll::memory::FuncPtr g_targetPresent1            = nullptr;
ll::memory::FuncPtr g_detourPresent1            = nullptr;
ll::memory::FuncPtr g_targetResizeBuffers       = nullptr;
ll::memory::FuncPtr g_detourResizeBuffers       = nullptr;
ll::memory::FuncPtr g_targetExecuteCommandLists = nullptr;
ll::memory::FuncPtr g_detourExecuteCommandLists = nullptr;

// D3D11
ID3D11Device*        g_pd3d11Device        = nullptr;
ID3D11DeviceContext* g_pd3d11DeviceContext = nullptr;

// D3D11On12 (for D3D12 mode)
ID3D11On12Device*   g_d3d11On12Device   = nullptr;
ID3D12CommandQueue* g_pGameCommandQueue = nullptr;

HWND              g_hWnd = nullptr;
std::atomic<bool> g_initialized{false};
GraphicsAPI       g_currentAPI = GraphicsAPI::Unknown;

// shutdown 标志：置位后渲染 hook 立即短路，不再触碰 ImGui/D3D 资源与缓存
std::atomic<bool> g_shuttingDown{false};
// 已进入渲染路径的帧计数：shutdown 释放资源前等待其归零
std::atomic<int> g_renderInFlight{0};

// 窗口过程子类化：游戏在 WM_SETCURSOR 里把光标设为隐藏光标，
// 大地图打开时拦截该消息强制显示箭头光标
WNDPROC g_origWndProc = nullptr;

LRESULT CALLBACK wndProcHook(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (!g_shuttingDown.load(std::memory_order_acquire) && msg == WM_SETCURSOR
        && MapState::getInstance().showWorldMap) {
        SetCursor(LoadCursorW(nullptr, IDC_ARROW));
        return TRUE;
    }
    if (g_origWndProc) return CallWindowProcW(g_origWndProc, hwnd, msg, wParam, lParam);
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void installWndProcHook() {
    if (g_hWnd && !g_origWndProc) {
        g_origWndProc = reinterpret_cast<WNDPROC>(
            SetWindowLongPtrW(g_hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&wndProcHook))
        );
    }
}

void removeWndProcHook() {
    if (g_hWnd && g_origWndProc) {
        // 仅当链顶仍是我们的 hook 时才还原：若其他 mod 在我们之后又子类化了同一窗口，
        // 硬写会把它从链上摘掉；此时保留链不动，wndProcHook 自身靠 g_shuttingDown 直通
        if (GetWindowLongPtrW(g_hWnd, GWLP_WNDPROC) == reinterpret_cast<LONG_PTR>(&wndProcHook)) {
            SetWindowLongPtrW(g_hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(g_origWndProc));
            g_origWndProc = nullptr;
        }
    }
}

void shutdownImGui() {
    if (g_initialized) {
        ImGui_ImplDX11_Shutdown();
        ImGui::DestroyContext();
        g_initialized = false;
        g_currentAPI  = GraphicsAPI::Unknown;
    }
}

void cleanupD3D11On12() {
    if (g_d3d11On12Device) {
        g_d3d11On12Device->Release();
        g_d3d11On12Device = nullptr;
    }
    if (g_pGameCommandQueue) {
        g_pGameCommandQueue->Release();
        g_pGameCommandQueue = nullptr;
    }
}

void __stdcall hkExecuteCommandLists(
    ID3D12CommandQueue*       pQueue,
    UINT                      NumCommandLists,
    ID3D12CommandList* const* ppCommandLists
) {
    if (!g_pGameCommandQueue) {
        D3D12_COMMAND_QUEUE_DESC desc = pQueue->GetDesc();
        if (desc.Type == D3D12_COMMAND_LIST_TYPE_DIRECT) {
            g_pGameCommandQueue = pQueue;
            g_pGameCommandQueue->AddRef();
        }
    }
    oExecuteCommandLists(pQueue, NumCommandLists, ppCommandLists);
}

HRESULT __stdcall hkResizeBuffers(
    IDXGISwapChain* pSwapChain,
    UINT            BufferCount,
    UINT            Width,
    UINT            Height,
    DXGI_FORMAT     NewFormat,
    UINT            SwapChainFlags
) {
    if (g_initialized) {
        ImGui_ImplDX11_Shutdown();
        ImGui::DestroyContext();
        g_initialized = false;
        g_currentAPI  = GraphicsAPI::Unknown;
    }
    return oResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

bool initGraphics(IDXGISwapChain* pSwapChain) {
    if (g_initialized) return true;

    // Try D3D11 first
    HRESULT hr11 = pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_pd3d11Device);
    if (SUCCEEDED(hr11)) {
        g_currentAPI = GraphicsAPI::D3D11;
        g_pd3d11Device->GetImmediateContext(&g_pd3d11DeviceContext);
    } else {
        // D3D12 mode - use D3D11On12
        if (!g_pGameCommandQueue) return false;

        ID3D12Device* pD3D12Device = nullptr;
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D12Device), (void**)&pD3D12Device))) {
            if (SUCCEEDED(D3D11On12CreateDevice(
                    pD3D12Device,
                    D3D11_CREATE_DEVICE_BGRA_SUPPORT,
                    nullptr,
                    0,
                    (IUnknown**)&g_pGameCommandQueue,
                    1,
                    0,
                    &g_pd3d11Device,
                    &g_pd3d11DeviceContext,
                    nullptr
                ))) {
                g_pd3d11Device->QueryInterface(__uuidof(ID3D11On12Device), (void**)&g_d3d11On12Device);
                g_currentAPI = GraphicsAPI::D3D12;
            }
            pD3D12Device->Release();
        }
    }

    if (g_pd3d11Device) {
        DXGI_SWAP_CHAIN_DESC sd;
        pSwapChain->GetDesc(&sd);
        g_hWnd = sd.OutputWindow;
        if (!g_hWnd) g_hWnd = FindWindowW(L"Minecraft", NULL);
        installWndProcHook();

        ImGui::CreateContext();
        ImGuiIO& io     = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.Fonts->AddFontFromFileTTF(
            "c:\\Windows\\Fonts\\msyh.ttc",
            config::getConfig().fontSize,
            NULL,
            io.Fonts->GetGlyphRangesChineseFull()
        );

        ImGui_ImplDX11_Init(g_pd3d11Device, g_pd3d11DeviceContext);
        g_initialized = true;
        return true;
    }

    return false;
}

void renderImGuiFrame(ID3D11RenderTargetView* rtv) {
    g_pd3d11DeviceContext->OMSetRenderTargets(1, &rtv, NULL);

    ImGuiIO& io = ImGui::GetIO();

    if (g_hWnd) {
        RECT rect;
        if (GetClientRect(g_hWnd, &rect)) {
            io.DisplaySize =
                ImVec2(static_cast<float>(rect.right - rect.left), static_cast<float>(rect.bottom - rect.top));
        }
    }

    static auto s_lastFrameTime = std::chrono::steady_clock::now();
    auto        now             = std::chrono::steady_clock::now();
    float       dt              = std::chrono::duration<float>(now - s_lastFrameTime).count();
    s_lastFrameTime             = now;
    io.DeltaTime                = dt > 0.0f ? dt : 1.0f / 60.0f;

    ImGui_ImplDX11_NewFrame();
    ImGui::NewFrame();

    MiniMapRenderer::getInstance().render();
    // 大地图最后绘制：全屏不透明背景会盖住小地图（同时小地图的 bake 调度仍在运行）
    WorldMapRenderer::getInstance().render();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    ID3D11RenderTargetView* nullRTV = nullptr;
    g_pd3d11DeviceContext->OMSetRenderTargets(1, &nullRTV, NULL);
    rtv->Release();
}

void RenderImGui(IDXGISwapChain* pSwapChain) {
    if (g_shuttingDown.load(std::memory_order_acquire)) return;

    g_renderInFlight.fetch_add(1, std::memory_order_acq_rel);
    struct InFlightGuard {
        ~InFlightGuard() { g_renderInFlight.fetch_sub(1, std::memory_order_acq_rel); }
    } guard;
    // 计数后再查一次：关闭恰好落在两次检查之间时，避免在资源释放后仍继续渲染
    if (g_shuttingDown.load(std::memory_order_acquire)) return;

    if (!g_initialized) {
        if (!initGraphics(pSwapChain)) return;
    }

    if (g_d3d11On12Device) {
        // D3D12 mode
        UINT             bufferIndex = 0;
        IDXGISwapChain3* pSwapChain3 = nullptr;
        if (SUCCEEDED(pSwapChain->QueryInterface(__uuidof(IDXGISwapChain3), (void**)&pSwapChain3))) {
            bufferIndex = pSwapChain3->GetCurrentBackBufferIndex();
            pSwapChain3->Release();
        }

        ID3D12Resource* d3d12BackBuffer = nullptr;
        if (SUCCEEDED(pSwapChain->GetBuffer(bufferIndex, __uuidof(ID3D12Resource), (void**)&d3d12BackBuffer))) {
            ID3D11Resource*      wrappedBackBuffer = nullptr;
            D3D11_RESOURCE_FLAGS d3d11Flags        = {D3D11_BIND_RENDER_TARGET};

            if (SUCCEEDED(g_d3d11On12Device->CreateWrappedResource(
                    d3d12BackBuffer,
                    &d3d11Flags,
                    D3D12_RESOURCE_STATE_PRESENT,
                    D3D12_RESOURCE_STATE_PRESENT,
                    __uuidof(ID3D11Resource),
                    (void**)&wrappedBackBuffer
                ))) {

                ID3D11RenderTargetView* rtv = nullptr;
                g_pd3d11Device->CreateRenderTargetView(wrappedBackBuffer, NULL, &rtv);

                g_d3d11On12Device->AcquireWrappedResources(&wrappedBackBuffer, 1);

                if (rtv) renderImGuiFrame(rtv);

                g_d3d11On12Device->ReleaseWrappedResources(&wrappedBackBuffer, 1);
                wrappedBackBuffer->Release();

                g_pd3d11DeviceContext->ClearState();
                g_pd3d11DeviceContext->Flush();
            }
            d3d12BackBuffer->Release();
        }
    } else {
        // D3D11 mode
        ID3D11Texture2D* pBackBuffer = nullptr;
        if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer))) {
            ID3D11RenderTargetView* rtv = nullptr;
            g_pd3d11Device->CreateRenderTargetView(pBackBuffer, NULL, &rtv);
            pBackBuffer->Release();

            if (rtv) {
                renderImGuiFrame(rtv);
                g_pd3d11DeviceContext->ClearState();
                g_pd3d11DeviceContext->Flush();
            }
        }
    }
}

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
    RenderImGui(pSwapChain);
    return oPresent(pSwapChain, SyncInterval, Flags);
}

HRESULT __stdcall hkPresent1(
    IDXGISwapChain1*               pSwapChain,
    UINT                           SyncInterval,
    UINT                           Flags,
    const DXGI_PRESENT_PARAMETERS* pParams
) {
    RenderImGui(pSwapChain);
    return oPresent1(pSwapChain, SyncInterval, Flags, pParams);
}

} // namespace

bool init() {
    g_shuttingDown.store(false, std::memory_order_release);

    HWND hwnd = FindWindowW(L"Minecraft", NULL);
    if (!hwnd) hwnd = GetForegroundWindow();
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
        void** pVTable = *reinterpret_cast<void***>(dummySwapChain);

        // Hook Present (VTable[8])
        Present_t presentPtr = reinterpret_cast<Present_t>(pVTable[8]);
        g_targetPresent      = ll::memory::toFuncPtr(presentPtr);
        g_detourPresent      = ll::memory::toFuncPtr(&hkPresent);
        ll::memory::hook(
            g_targetPresent,
            g_detourPresent,
            reinterpret_cast<ll::memory::FuncPtr*>(&oPresent),
            ll::memory::HookPriority::Normal
        );

        // Hook ResizeBuffers (VTable[13])
        ResizeBuffers_t resizeBuffersPtr = reinterpret_cast<ResizeBuffers_t>(pVTable[13]);
        g_targetResizeBuffers            = ll::memory::toFuncPtr(resizeBuffersPtr);
        g_detourResizeBuffers            = ll::memory::toFuncPtr(&hkResizeBuffers);
        ll::memory::hook(
            g_targetResizeBuffers,
            g_detourResizeBuffers,
            reinterpret_cast<ll::memory::FuncPtr*>(&oResizeBuffers),
            ll::memory::HookPriority::Normal
        );

        // Hook Present1 (VTable[22]) if available
        IDXGISwapChain1* dummySwapChain1 = nullptr;
        if (SUCCEEDED(dummySwapChain->QueryInterface(__uuidof(IDXGISwapChain1), (void**)&dummySwapChain1))) {
            void**     pVTable1    = *reinterpret_cast<void***>(dummySwapChain1);
            Present1_t present1Ptr = reinterpret_cast<Present1_t>(pVTable1[22]);
            g_targetPresent1       = ll::memory::toFuncPtr(present1Ptr);
            g_detourPresent1       = ll::memory::toFuncPtr(&hkPresent1);
            ll::memory::hook(
                g_targetPresent1,
                g_detourPresent1,
                reinterpret_cast<ll::memory::FuncPtr*>(&oPresent1),
                ll::memory::HookPriority::Normal
            );
            dummySwapChain1->Release();
        }

        dummySwapChain->Release();
        dummyDevice->Release();
        dummyContext->Release();

        // Hook D3D12 CommandQueue::ExecuteCommandLists (for D3D12 mode detection)
        ID3D12Device* pDummyD12Device = nullptr;
        if (SUCCEEDED(
                D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), (void**)&pDummyD12Device)
            )) {
            D3D12_COMMAND_QUEUE_DESC queueDesc = {};
            queueDesc.Type                     = D3D12_COMMAND_LIST_TYPE_DIRECT;
            ID3D12CommandQueue* pDummyQueue    = nullptr;
            if (SUCCEEDED(
                    pDummyD12Device->CreateCommandQueue(&queueDesc, __uuidof(ID3D12CommandQueue), (void**)&pDummyQueue)
                )) {
                void** pVTable12 = *reinterpret_cast<void***>(pDummyQueue);
                // VTable[10] is ExecuteCommandLists
                ExecuteCommandLists_t executeCommandListsPtr = reinterpret_cast<ExecuteCommandLists_t>(pVTable12[10]);
                g_targetExecuteCommandLists                  = ll::memory::toFuncPtr(executeCommandListsPtr);
                g_detourExecuteCommandLists                  = ll::memory::toFuncPtr(&hkExecuteCommandLists);
                ll::memory::hook(
                    g_targetExecuteCommandLists,
                    g_detourExecuteCommandLists,
                    reinterpret_cast<ll::memory::FuncPtr*>(&oExecuteCommandLists),
                    ll::memory::HookPriority::Normal
                );
                pDummyQueue->Release();
            }
            pDummyD12Device->Release();
        }

        return true;
    }

    return false;
}

void shutdown() {
    // 先短路渲染路径，再等待已进来的帧退出，之后才能安全释放 ImGui/D3D 资源
    g_shuttingDown.store(true, std::memory_order_release);
    // 最多等 2s：渲染线程若已随客户端关闭卡死，不能让 disable 跟着挂死
    for (int i = 0; i < 200 && g_renderInFlight.load(std::memory_order_acquire) > 0; ++i) {
        Sleep(10);
    }

    if (g_targetPresent && g_detourPresent) {
        ll::memory::unhook(g_targetPresent, g_detourPresent);
    }
    if (g_targetPresent1 && g_detourPresent1) {
        ll::memory::unhook(g_targetPresent1, g_detourPresent1);
    }
    if (g_targetResizeBuffers && g_detourResizeBuffers) {
        ll::memory::unhook(g_targetResizeBuffers, g_detourResizeBuffers);
    }
    if (g_targetExecuteCommandLists && g_detourExecuteCommandLists) {
        ll::memory::unhook(g_targetExecuteCommandLists, g_detourExecuteCommandLists);
    }
    shutdownImGui();
    removeWndProcHook();
    if (g_pd3d11DeviceContext) {
        g_pd3d11DeviceContext->Release();
        g_pd3d11DeviceContext = nullptr;
    }
    if (g_pd3d11Device) {
        g_pd3d11Device->Release();
        g_pd3d11Device = nullptr;
    }
    cleanupD3D11On12();
    g_hWnd = nullptr;
}

GraphicsAPI getCurrentAPI() { return g_currentAPI; }

ID3D11Device* getDevice() { return g_pd3d11Device; }

ID3D11DeviceContext* getContext() { return g_pd3d11DeviceContext; }

HWND getHwnd() { return g_hWnd; }

} // namespace coral_map::DX11Hook