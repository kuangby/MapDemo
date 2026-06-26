#pragma once

#include <windows.h>

// 定义这些宏，避免与 LeviLamina 中的重复定义冲突
#define D3D12_FEATURE_DATA_D3D12_OPTIONS  D3D12_FEATURE_DATA_D3D12_OPTIONS_LEGACY
#define D3D12_FEATURE_DATA_ARCHITECTURE  D3D12_FEATURE_DATA_ARCHITECTURE_LEGACY
#define D3D12_RAYTRACING_GEOMETRY_DESC  D3D12_RAYTRACING_GEOMETRY_DESC_LEGACY

#include <d3d11.h>
#include <d3d12.h>
#include <d3d11on12.h>
#include <dxgi1_4.h>

// 取消这些宏定义，避免后续问题
#undef D3D12_FEATURE_DATA_D3D12_OPTIONS
#undef D3D12_FEATURE_DATA_ARCHITECTURE
#undef D3D12_RAYTRACING_GEOMETRY_DESC

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

namespace map_demo::DX11Hook {

enum class GraphicsAPI {
    Unknown,
    D3D11,
    D3D12
};

bool init();
void shutdown();
GraphicsAPI getCurrentAPI();

} // namespace map_demo::DX11Hook
