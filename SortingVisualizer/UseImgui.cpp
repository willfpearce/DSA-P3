#include <iostream>
#include <random>
#include <array>
#include <utility>
#include <chrono>
#include <fstream>

#include "UseImgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "ShellSort.h"
#include "imgui_internal.h"

std::random_device rd;
std::mt19937 gen(rd());

// loads state population and name data from its file
// returns arrays of the population data and the names
std::pair<float*, std::array<std::string, 1000> > UseImgui::loadStateData(const char* stateName) {
    std::string strStateName(stateName);
    // opening the file for reading
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

// this is the function that runs on a separate thread when the state or algorithm is changed
SortingAlgorithm* UseImgui::asyncChangeAlgoTask(const char* state, const char* type) {
    // check created algorithms map to determine if state/algo type combo already loaded
    std::string key = std::string(state) + type; // key for the map is just the state and algo type concatenated
    if (createdAlgos.count(key) != 0) { // if algo exists in the map
        createdAlgos[key]->reset(); // resets back to the first step of the sort
        return createdAlgos[key]; // returns previously constructed algo instead of a new one
    }

    // load from file
    std::pair<float*, std::array<std::string, 1000> > stateData = loadStateData(state);
    switch ((int)*type) {
        case (int) *"Merge Sort":
            // TODO implement merge sort
            newAlgo = new MergeSort(stateData.first, stateData.second);
            break;
        case (int) *"Shell Sort":
            newAlgo = new ShellSort(stateData.first, stateData.second);
            break;
        case (int) *"Quick Sort":
            newAlgo = new QuickSort(stateData.first, stateData.second);
            break;

    // NOTE: algorithm objects are constructed on the heap to prevent their destructors from being called prematurely
    // there are other ways to do this like the 'move' keyword
    }
    createdAlgos[key] = newAlgo;
    auto stepData = newAlgo->getNextStep();


    currentPlotData = stepData.first;
    currentNamesData = stepData.second;
    mode = PAUSED;
    return newAlgo;
}

UseImgui::UseImgui(Params params) : params(params) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); (void)io;

    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(params.hwnd);
    ImGui_ImplDX9_Init(params.g_pd3dDevice);

    // constructs default algorithm
    currentAlgoFuture = std::async(std::launch::async, &UseImgui::asyncChangeAlgoTask, this, "Alabama", "Merge Sort");
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
    if (!loading && !currentAlgo->areNoStepsRemaining())
    {
        auto stepData = currentAlgo->getNextStep();
        currentPlotData = stepData.first;
        currentNamesData = stepData.second;
    }
}

void UseImgui::stepBack() {
    if (!loading && !currentAlgo->isAtStart())
    {
        auto stepData = currentAlgo->getPreviousStep();
        currentPlotData = stepData.first;
        currentNamesData = stepData.second;
    }
}

// Where all imgui rendering code is located, all logic for the sorting visualization and its parameters
void UseImgui::Render() {
    // Start the Dear ImGui frame
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // Create options window
    {
        // set options window to max width and height
        ImGui::SetNextWindowSize(io->DisplaySize);
        ImGui::SetNextWindowPos({0, 0});

        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;
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

        // Step back button
        ImGui::SameLine(0, 25);
        if (ImGui::Button("<- Step")) {
            mode = PAUSED;
            stepBack();
        }

        // Pause/Play button
        ImGui::SameLine(0, 6);
        if (ImGui::Button(mode == PAUSED ? "Play" : "Pause")) {
            mode = mode == PAUSED ? PLAYING : PAUSED;
            if (mode != PAUSED){
                lastStepTime = std::chrono::system_clock::now();
            }
        }

        // Step forward button
        ImGui::SameLine(0, 6);
        if (ImGui::Button("Step ->")) {
            mode = PAUSED;
            stepForward();
        }

        // Reverse button
        ImGui::SameLine(0, 6);
        if (ImGui::Button("Reverse")) {
            if (mode != REVERSE) {
                mode = REVERSE;
            } else {
                mode = PAUSED;
            }
        }

        // Reset visualization button
        ImGui::SameLine(0, 6);
        if (ImGui::Button("Reset")) {
            mode = PAUSED;
            if (!loading) {
                currentAlgo->reset();
                stepForward();
            }
        }

        // Playing mode status indicator
        ImGui::SameLine(0, 10);
        if (mode == PAUSED)
            ImGui::Text("Mode: Paused");
        else if (mode == PLAYING)
            ImGui::Text("Mode: Playing");
        else
            ImGui::Text("Mode: Reverse");



        // create visualization
        ImGui::InvisibleButton("padding", {5, 5}); // padding
        ImGui::SeparatorText("Visualization"); // Title

        // visualization only displays when sorting algorithm future has a valid result or not loading
        if (!loading || (currentAlgoFuture.valid() && currentAlgoFuture.wait_for(std::chrono::milliseconds(1)) == std::future_status::ready)) {
            // sets loading to false when the asynchronous function is finished
            if (loading) {
                loading = false;
                currentAlgo = currentAlgoFuture.get(); // retrieve sorting results from the future object
            }

            // here we have the logic for stepping through the visualization at the correct speed if the mode == playing
            if (mode != PAUSED) {
                std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
                std::chrono::seconds oneSecond(1);
                if (now >= (lastStepTime + (oneSecond / (stepSpeed * 2)))) {
                    if (mode != REVERSE) {
                        stepForward();
                    } else {
                        stepBack();
                    }
                    lastStepTime = std::chrono::system_clock::now();
                }
            }

            const float scaleMin = 10000.0f; // lowest pop size
            const float scaleMax = 1000000.0f; // highest pop size
            ImGui::SetNextItemWidth(ImGui::GetWindowWidth() * 0.99);
            ImGui::PushStyleColor(ImGuiCol_PlotLines, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); // styling
            ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); // styling
            ImGui::PlotHistogram("", currentPlotData, 1000, 0, nullptr, scaleMin, scaleMax, {0.0f, 575.0f}); // current sort step is rendered
            ImGui::PopStyleColor(2);
            if (ImGui::IsItemHovered()) { // logic for showing tooltip with city name and population on hover
                int pos = (int)((io->MousePos.x - 12) / 1231 * 1000 + 1);
                if (pos < 0) pos = 0;
                if (pos > 999) pos = 999;
                ImGui::SetTooltip("%s\nPop: %.0f", currentNamesData[pos].c_str(), currentPlotData[pos]);
            }

            // Analysis section
            ImGui::SeparatorText("Analysis");
            ImGui::Text("System Time Elapsed: %d ms", currentAlgo->getSortTime().count());
            ImGui::Text("Number of Swaps: %d", currentAlgo->getSwapCount());

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

// destructor, runs on program exit
UseImgui::~UseImgui() {
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    // delete all stored SortingAlgorithm objects to prevent memory leaks
    for (auto it = createdAlgos.begin(); it != createdAlgos.end(); ++it) {
        delete it->second;
    }
}

void UseImgui::ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = params.g_pd3dDevice->Reset(&params.g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

