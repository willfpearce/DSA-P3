#include <iostream>
#include <random>
#include <array>
#include <utility>
#include <chrono>
#include <fstream>

#include "UseImgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
//#include "MergeSort.h"
#include "QuickSort.h"
#include "ShellSort.h"

std::random_device rd;
std::mt19937 gen(rd());

int getRandom(int low, int high){
    std::uniform_int_distribution<int> distribution(low, high);
    return distribution(gen);
}

std::pair<float*, std::array<std::string, 1000> > UseImgui::loadStateData(const char* stateName) {
    std::string strStateName(stateName);
    std::ifstream stream("./resources/states/" + strStateName + ".txt");

    float* pops = new float[1000];
    std::array<std::string, 1000> names;
    std::string line;
    for (int i = 0; i < 1000; i++) {
        std::getline(stream, line);
        pops[i] = (float)stoi(line);
    }
    for (int i = 0; i < 1000; i++) {
        std::getline(stream, line);
        names[i] = line;
    }
    return std::make_pair(pops, names);
}

// needs to be updated
SortingAlgorithm UseImgui::asyncChangeAlgoTask(const char* state, const char* type) {
    // check created algorithms map to determine if state/algo type combo already loaded
    std::string key = std::string(state) + type;
    if (createdAlgos.count(key) != 0) {
        createdAlgos[key].reset();
        return createdAlgos[key];
    }

    std::pair<float*, std::array<std::string, 1000> > stateData = loadStateData(state);
    SortingAlgorithm newAlgo;
    switch ((int)*type) {
        case (int) *"Merge Sort":
            // TODO implement merge sort
            newAlgo = QuickSort(stateData.first, stateData.second);
            break;
        case (int) *"Shell Sort":
            newAlgo = ShellSort(stateData.first, stateData.second);
            break;
        case (int) *"Quick Sort":
            newAlgo =  QuickSort(stateData.first, stateData.second);
            break;
    }
    createdAlgos[key] = newAlgo;
    auto stepData = newAlgo.getNextStep();


    currentPlotData = stepData.first;
    currentNamesData = stepData.second;
    paused = true;
    return newAlgo;
}

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

    currentAlgoFuture = std::async(std::launch::async, &UseImgui::asyncChangeAlgoTask, this, "Alabama", "Quick Sort");
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

// called every time the state or sorting algorithm is changed
// runs the SortingAlgorithm constructors asynchronously
void UseImgui::ChangeAlgo() {
    loading = true;
    currentAlgoFuture = std::async(std::launch::async, &UseImgui::asyncChangeAlgoTask, this, currentState, currentAlgoType);
}

void UseImgui::stepForward() {
    if (!loading && !currentAlgo.areNoStepsRemaining())
    {
        auto stepData = currentAlgo.getNextStep();
        currentPlotData = stepData.first;
        currentNamesData = stepData.second;
    }
}

void UseImgui::stepBack() {
    if (!loading && !currentAlgo.isAtStart())
    {
        auto stepData = currentAlgo.getPreviousStep();
        currentPlotData = stepData.first;
        currentNamesData = stepData.second;
    }
}

void UseImgui::Render() {
    // Start the Dear ImGui frame
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // Create options window
    {
        // TODO: we need to create a system for updating the sorting visualizer iff the step time has elapsed
        // TODO: create pause functionality

        // set options window to max width and height
        ImGui::SetNextWindowSize(io->DisplaySize);
        ImGui::SetNextWindowPos({0, 0});

        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar;
        ImGui::Begin("Options", nullptr, windowFlags); // Create a window called "Options" and append into it.

        // Title
        ImGui::SeparatorText("Options");

        // State Selector Dropdown
        ImGui::SetNextItemWidth(130);
        if (ImGui::BeginCombo("State", currentState))
        {
            for (int i = 0; i < numStates; i++)
            {
                bool isSelected = (currentState == states[i]);
                if (ImGui::Selectable(states[i], isSelected)) {
                    currentState = states[i];
                    ChangeAlgo();
                }

                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        // Sorting Algorithm drop down
        ImGui::SameLine(0, 25);
        ImGui::SetNextItemWidth(100);

        if (ImGui::BeginCombo("Sorting Algorithm", currentAlgoType))
        {
            for (int i = 0; i < numAlgos; i++)
            {
                bool isSelected = (currentAlgoType == algos[i]);
                if (ImGui::Selectable(algos[i], isSelected)) {
                    currentAlgoType = algos[i];
                    ChangeAlgo();
                }

                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        // Step Speed Slider
        ImGui::SameLine(0, 25);
        ImGui::SetNextItemWidth(250);
        ImGui::SliderInt("Step Speed", &stepSpeed, minSpeed, maxSpeed);

        ImGui::SameLine(0, 25);
        if (ImGui::Button("<- Step")) {
            paused = true;
            stepBack();
        }

        ImGui::SameLine(0, 6);
        if (ImGui::Button("Pause")) {
            paused = !paused;
            if(!paused){
                lastStepTime = std::chrono::system_clock::now();
            }
            std::cout << (paused ? "Paused!" : "Now Playing!") << "\n";
        }

        ImGui::SameLine(0, 6);
        if (ImGui::Button("Step ->")) {
            paused = true;
            stepForward();
        }

        ImGui::SameLine(0, 10);
        ImGui::Text(paused ? "Mode: Paused" : "Mode: Playing");

        // create visualization
        ImGui::InvisibleButton("padding", {5, 5}); // padding
        ImGui::SeparatorText("Visualization"); // Title

        // visualization only displays when sorting algorithm future has a valid result
        if (!loading || (currentAlgoFuture.valid() && currentAlgoFuture.wait_for(std::chrono::milliseconds(1)) == std::future_status::ready)) {
            if (loading) {
                loading = false;
                currentAlgo = currentAlgoFuture.get();
            }
            if(!paused){
                std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
                std::chrono::seconds oneSecond(1);
                if(now >= (lastStepTime + (oneSecond / (stepSpeed * 2)))){
                    stepForward();
                    lastStepTime = std::chrono::system_clock::now();
                }
            }

            // these variables represent the lowest and highest values of the population, so they'll change when we figure out how we're generating the data
            const float scaleMin = 10000.0f;
            const float scaleMax = 1000000.0f;
            ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.99);
            ImGui::PlotHistogram("", currentPlotData, 1000, 0, nullptr, scaleMin, scaleMax, {0.0f, 575.0f});
        } else {
            ImGui::Text("Loading...");
        }

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

