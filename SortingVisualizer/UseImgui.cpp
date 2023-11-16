#include <iostream>
#include "UseImgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

UseImgui::UseImgui(Params params) : params(params) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); (void)io;

    // could be unnecessary if keyboard unused but leaving it here for now
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(params.hwnd);
    ImGui_ImplDX9_Init(params.g_pd3dDevice);

    // TODO: set up class state: current algo/state, step speed
}


// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
void UseImgui::Update(bool& done) {
    // Poll and handle messages (inputs, window resize, etc.)
    // See the WndProc() function below for our to dispatch events to the Win32 backend.
    MSG msg;
    while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
        if (msg.message == WM_QUIT)
            done = true;
    }
    if (done)
        return;

    // Handle window resize (we don't resize directly in the WM_SIZE handler)
    if (params.g_ResizeWidth != 0 && params.g_ResizeHeight != 0)
    {
        params.g_d3dpp.BackBufferWidth = params.g_ResizeWidth;
        params.g_d3dpp.BackBufferHeight = params.g_ResizeHeight;
        params.g_ResizeWidth = params.g_ResizeHeight = 0;
        ResetDevice();
    }
}

void UseImgui::Render() {
    // Start the Dear ImGui frame
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();

    // Create options window
    // TODO: Possibly change formatting for options to be along one line on top?
    {
        // TODO: store static variables as class member variables so they are accessible in all functions
        // TODO: we need to create a system for updating the sorting visualizer iff the step time has elapsed
        // TODO: we need to create a system for changing the visualization if the state or sorting algorithm is changed
        // TODO: create pause functionality

        ImGui::Begin("Options"); // Create a window called "Options" and append into it.

        static int currentState = 0;
        const char* states[] = {"Florida", "California", "Texas"};
        static int numStates = 3;
        ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.30);
        ImGui::Combo("State", &currentState, states, numStates); // Dropdown of items in states[]

        static int currentAlgo;
        const char* algos[] = {"Merge", "Shell", "Quick"};
        ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.30);
        ImGui::Combo("Sorting Algorithm", &currentAlgo, algos, 3); // Dropdown of Sorting algos

        static int stepSpeed = 3;
        int minSpeed = 1;
        int maxSpeed = 5;
        ImGui::SliderInt("Step Speed", &stepSpeed, minSpeed, maxSpeed);

        if (ImGui::Button("-"))
            stepSpeed = stepSpeed > minSpeed ? stepSpeed - 1 : stepSpeed;
        ImGui::SameLine(ImGui::GetWindowWidth() * 0.075);

        static int paused = true;
        if (ImGui::Button("Pause")) {
            paused = !paused;
            std::cout << (paused ? "Paused!" : "Now Playing!") << "\n";
        }

        ImGui::SameLine(ImGui::GetWindowWidth() * 0.2);
        if (ImGui::Button("+"))
            stepSpeed = stepSpeed < maxSpeed ? stepSpeed + 1 : stepSpeed;

        ImGui::SameLine(ImGui::GetWindowWidth() * 0.275);
        ImGui::Text(paused ? "Mode: Paused" : "Mode: Playing");

        ImGui::End();
    }

    // create visualization window
    {
        ImGui::Begin("Visualization");
        const float values[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};

        ImGui::PlotHistogram("Data", values, 10);

        ImGui::End();
    }

    // Rendering
    ImGui::EndFrame();

    ImVec4 clear_color(0.5, 0.75, 1.0, 1.0);

    params.g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
    params.g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    params.g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
    D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x*clear_color.w*255.0f), (int)(clear_color.y*clear_color.w*255.0f), (int)(clear_color.z*clear_color.w*255.0f), (int)(clear_color.w*255.0f));
    params.g_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
    if (params.g_pd3dDevice->BeginScene() >= 0)
    {
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
        params.g_pd3dDevice->EndScene();
    }
    HRESULT result = params.g_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);

    // Handle loss of D3D9 device
    if (result == D3DERR_DEVICELOST && params.g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
        ResetDevice();
}

UseImgui::~UseImgui() {
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void UseImgui::ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = params.g_pd3dDevice->Reset(&params.g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

