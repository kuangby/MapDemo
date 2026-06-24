#pragma once

#include <d3d11.h>
#include <dxgi.h>
#include <windows.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

// namespace {

namespace map_demo::DX11Hook {

bool init();
void shutdown();

} // namespace map_demo::DX11Hook

// } // namespace
