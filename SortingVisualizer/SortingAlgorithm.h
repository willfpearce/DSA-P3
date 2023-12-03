#include <array>
#include <utility>
#include <vector>
#include <string>
#include <chrono>

#pragma once

class SortingAlgorithm {
protected:
    std::vector<float*> sortingSteps; //Stores every iteration of the data as it is being sorted.
    std::vector<std::array<std::string, 1000> > namesSortingSteps; //Stores every iteration of the names of the data as it is being sorted.
    int currentStep = -1; //Stores the current step in the iterations of the sorting steps. Used to track frames in visualization.
    float* copyFloatPointer(float* rhs); //Creates a copy of a float array pointer. Used to make sure arrays in sorting steps are not the same object still being edited.
    int swapCount = 0; //Keeps a count of how many swaps were preformed in the sorting algorithm.
    std::chrono::duration<int,std::milli> sortTime; //Stores the real time it took for the sorting algorithm to execute in milliseconds.

public:
    std::pair<float*, std::array<std::string, 1000> > getNextStep(); //Returns the arrays for the next step.
    std::pair<float*, std::array<std::string, 1000> > getPreviousStep(); //Returns the arrays for the previous step.
    bool areNoStepsRemaining(); //Checks if the last step is reached.
    bool isAtStart(); //Checks if the current step is the first step.
    std::pair<float*, std::array<std::string, 1000> > getSorted();
    void reset(); //Resets the current step.
    int getSwapCount(); //Getter function for the swap count.
    std::chrono::duration<int,std::milli> getSortTime(); //Getter function for the sort time.

    ~SortingAlgorithm(); //Class destructor
};
