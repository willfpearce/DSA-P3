// Dear ImGui: standalone example application for DirectX 9

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

#include "UseImgui.h"
#include "DX9Window.h"
#include "proc.h"

// Main code
int main(int, char**)
{
    DX9Window window(g_pD3D, g_pd3dDevice, g_ResizeWidth, g_ResizeHeight, g_d3dpp);
    if (!window.InitWindow())
        return 1;

    UseImgui imguiObj(window.getParams());

    // Main loop
    bool done = false;
    while (!done)
    {
        imguiObj.Update(done);
        if (done)
            break;

        imguiObj.Render();
    }


    return 0;
}

// Helper functions
