#include <array>
#include <utility>
#include <vector>
#include <string>

#pragma once

class SortingAlgorithm {
protected:
    std::vector<float*> sortingSteps;
    std::vector<std::array<std::string, 1000> > namesSortingSteps;
    size_t currentStep = -1;
    float* copyFloatPointer(float* rhs);
public:
    std::pair<float*, std::array<std::string, 1000> > getNextStep();
    std::pair<float*, std::array<std::string, 1000> > getPreviousStep();
    bool areNoStepsRemaining();
    bool isAtStart();
    std::pair<float*, std::array<std::string, 1000> > getSorted();
    void reset();
};
