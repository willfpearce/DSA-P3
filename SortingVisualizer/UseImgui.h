#pragma once

#include <future>
#include <unordered_map>
#include "imgui.h"
#include "params.h"
#include "SortingAlgorithm.h"

static const char* states[] = {"Alabama", "Alaska", "Arizona", "Arkansas", "California", "Colorado", "Connecticut",
                        "Delaware", "Florida", "Georgia", "Hawaii", "Idaho", "Illinois", "Indiana",
                        "Iowa", "Kansas", "Kentucky", "Louisiana", "Maine", "Maryland", "Massachusetts",
                        "Michigan", "Minnesota", "Mississippi", "Missouri", "Montana", "Nebraska", "Nevada",
                        "New Hampshire", "New Jersey", "New Mexico", "New York", "North Carolina", "North Dakota",
                        "Ohio", "Oklahoma", "Oregon", "Pennsylvania", "Rhode Island", "South Carolina",
                        "South Dakota", "Tennessee", "Texas", "Utah", "Vermont", "Virginia", "Washington",
                        "West Virginia", "Wisconsin", "Wyoming"};

static const char* algos[] = {"Merge Sort", "Shell Sort", "Quick Sort"};

class UseImgui {
private:
    ImGuiIO* io;
    void ResetDevice();
    Params params;

    const int numStates = 50;
    const char* currentState = states[0];

    const int numAlgos = 3;
    const char* currentAlgoType = algos[0];

    int stepSpeed = 3;
    const int minSpeed = 1;
    const int maxSpeed = 5;
    enum PlayingMode {PAUSED, PLAYING, REVERSE};
    PlayingMode mode = PAUSED;
    bool loading = true;

    std::chrono::system_clock::time_point lastStepTime;

    float* currentPlotData;
    std::array<std::string, 1000> currentNamesData;

    std::future<SortingAlgorithm*> currentAlgoFuture;
    SortingAlgorithm* currentAlgo;
    std::unordered_map<std::string, SortingAlgorithm*> createdAlgos;
    SortingAlgorithm* newAlgo;

    void ChangeAlgo();
    SortingAlgorithm* asyncChangeAlgoTask(const char* state, const char* type);
    std::pair<float*, std::array<std::string, 1000> > loadStateData(const char* stateName);

    void stepForward();
    void stepBack();

public:
    UseImgui(Params params);
    void Update(bool& done);
    void Render();
    ~UseImgui();
};
