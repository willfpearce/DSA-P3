#include <array>
#include <utility>
#include <vector>
#include <string>

#pragma once

class SortingAlgorithm {
protected:
    std::vector<std::array<std::pair<std::string, int>, 1000>> sortingSteps;
    size_t currentStep;
public:
    std::array<std::pair<std::string, int>, 1000> getNextStep();
    std::array<std::pair<std::string, int>, 1000> getPreviousStep();
    bool areNoStepsRemaining();
};
