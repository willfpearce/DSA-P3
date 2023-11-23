#pragma once

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
    int paused = true;

    // TODO make use of future library to run SortingAlgorithm constructors on separate thread and show loading message
    SortingAlgorithm currentAlgo;

    void ChangeAlgo();

public:
    UseImgui(Params params);
    void Update(bool& done);
    void Render();
    ~UseImgui();
};
