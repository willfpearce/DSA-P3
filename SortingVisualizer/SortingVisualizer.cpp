// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

#include "UseImgui.h"
#include "DX9Window.h"
#include "params.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 775
#define WINDOW_TITLE L"Dear ImGui Sorting Visualizer"

// Main code
int main(int, char**)
{
    // set up window using DX9 and Win32 API
    DX9Window window(g_pD3D, g_pd3dDevice, g_ResizeWidth, g_ResizeHeight, g_d3dpp, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    if (!window.InitWindow()) // exit if there's a problem during window initialization
        return 1;

    // initializing object with window params
    // most application logic is contained in this class
    UseImgui imguiObj(window.getParams());

    // Main loop
    bool done = false;
    while (!done)
    {
        // function that handles messages and checks if the window should close
        imguiObj.Update(done);
        if (done)
            break;

        // function that handles GUI rendering and application logic
        imguiObj.Render();
    }


    return 0;
}
