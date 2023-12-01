#include <array>
#include <utility>
#include <vector>
#include <string>

#pragma once

class SortingAlgorithm {
protected:
    std::vector<float*> sortingSteps;
    size_t currentStep;
    float* copyFloatPointer(float* rhs);
public:
    float* getNextStep();
    float* getPreviousStep();
    bool areNoStepsRemaining();
    float* getSorted();
};
