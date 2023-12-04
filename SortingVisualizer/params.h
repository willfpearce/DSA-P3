#pragma once

#include <d3d9.h>

// Initialization of DirectX 9 window params
static LPDIRECT3D9              g_pD3D = nullptr;
static LPDIRECT3DDEVICE9        g_pd3dDevice = nullptr;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

// creating a struct for Params to pass them more easily
struct Params {
    LPDIRECT3DDEVICE9& g_pd3dDevice; UINT& g_ResizeWidth; UINT& g_ResizeHeight; D3DPRESENT_PARAMETERS& g_d3dpp;
    HWND hwnd;
    UINT windowWidth, windowHeight;
};

