#include <array>
#include <utility>
#include <vector>
#include <string>

#pragma once

class SortingAlgorithm {
private:
    std::vector<std::array<std::pair<std::string, int>, 50000>> sortingSteps;
    size_t currentStep;
public:
    std::array<std::pair<std::string, int>, 50000> getNextStep();
    std::array<std::pair<std::string, int>, 50000> getPreviousStep();
    bool areNoStepsRemaining();
};
