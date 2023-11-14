#pragma once

#include <d3d9.h>


struct Params {
    LPDIRECT3D9& g_pD3D; LPDIRECT3DDEVICE9& g_pd3dDevice; UINT& g_ResizeWidth; UINT& g_ResizeHeight; D3DPRESENT_PARAMETERS& g_d3dpp;
    WNDCLASSEXW wc;
    HWND hwnd;
};

