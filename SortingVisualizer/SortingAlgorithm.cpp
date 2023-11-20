#include "SortingAlgorithm.h"

std::array<std::pair<std::string, int>, 50000> SortingAlgorithm::getNextStep() {
    return sortingSteps[++currentStep];
}

std::array<std::pair<std::string, int>, 50000> SortingAlgorithm::getPreviousStep() {
    return sortingSteps[--currentStep];
}

bool SortingAlgorithm::areNoStepsRemaining() {
    return currentStep == sortingSteps.size() - 1;
}