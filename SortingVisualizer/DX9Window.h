#pragma once

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "params.h"
#include <d3d9.h>
#include <tchar.h>

// Creates and initializes window
class DX9Window {
private:
    WNDCLASSEXW wc;
    HWND hwnd;
    UINT windowWidth, windowHeight;

    LPDIRECT3D9& g_pD3D; LPDIRECT3DDEVICE9& g_pd3dDevice; UINT& g_ResizeWidth; UINT& g_ResizeHeight; D3DPRESENT_PARAMETERS& g_d3dpp;

    bool CreateDeviceD3D();
    void CleanupDeviceD3D();
public:
    DX9Window(LPDIRECT3D9& g_pD3D, LPDIRECT3DDEVICE9& g_pd3dDevice, UINT& g_ResizeWidth, UINT& g_ResizeHeight, D3DPRESENT_PARAMETERS& g_d3dpp, UINT windowWidth, UINT windowHeight, LPCWSTR windowTitle);
    bool InitWindow();
    Params getParams();
    ~DX9Window();
};