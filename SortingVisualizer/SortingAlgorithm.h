#include <array>
#include <utility>
#include <vector>
#include <string>
#include <chrono>

#pragma once

class SortingAlgorithm {
protected:
    std::vector<float*> sortingSteps;
    std::vector<std::array<std::string, 1000> > namesSortingSteps;
    int currentStep = -1;
    float* copyFloatPointer(float* rhs);
    int swapCount = 0;
    std::chrono::duration<int,std::milli> sortTime;

public:
    std::pair<float*, std::array<std::string, 1000> > getNextStep();
    std::pair<float*, std::array<std::string, 1000> > getPreviousStep();
    bool areNoStepsRemaining();
    bool isAtStart();
    std::pair<float*, std::array<std::string, 1000> > getSorted();
    void reset();
    int getSwapCount();
    std::chrono::duration<int,std::milli> getSortTime();


    ~SortingAlgorithm();
};
