#include "DX9Window.h"
#include "proc.h"
#include <string>

DX9Window::DX9Window(LPDIRECT3D9& g_pD3D, LPDIRECT3DDEVICE9& g_pd3dDevice, UINT& g_ResizeWidth, UINT& g_ResizeHeight, D3DPRESENT_PARAMETERS& g_d3dpp, UINT windowWidth, UINT windowHeight, LPCWSTR windowTitle) :
    g_pD3D(g_pD3D), g_pd3dDevice(g_pd3dDevice), g_ResizeWidth(g_ResizeWidth), g_ResizeHeight(g_ResizeHeight), g_d3dpp(g_d3dpp), windowWidth(windowWidth), windowHeight(windowHeight)
{
    std::string iconFileName = "resources\\icon.ico";
    HANDLE iconHandle = BeginUpdateResourceA(iconFileName.c_str(), false);

    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGui Example", nullptr };
    ::RegisterClassExW(&wc);
    hwnd = ::CreateWindowW(wc.lpszClassName, windowTitle, WS_OVERLAPPEDWINDOW, 100, 100, windowWidth, windowHeight, nullptr, nullptr, wc.hInstance, nullptr);
}

bool DX9Window::InitWindow() {
    // Initialize Direct3D
    if (!CreateDeviceD3D())
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return false;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);
    return true;
}

bool DX9Window::CreateDeviceD3D()
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

void DX9Window::CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = nullptr; }
}

Params DX9Window::getParams() {
    return {g_pd3dDevice, g_ResizeWidth, g_ResizeHeight, g_d3dpp, hwnd, windowWidth, windowHeight};
}

DX9Window::~DX9Window() {
    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
}


