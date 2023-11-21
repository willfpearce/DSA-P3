#pragma once

#include "imgui.h"
#include "params.h"

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

    int numStates = 50;
    const char* currentState = states[0];

    int numAlgos = 3;
    const char* currentAlgo = algos[0];

public:
    UseImgui(Params params);
    void Update(bool& done);
    void Render();
    ~UseImgui();
};
