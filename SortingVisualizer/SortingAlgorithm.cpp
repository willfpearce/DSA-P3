#include "SortingAlgorithm.h"
#include <iostream>

std::pair<float*, std::array<std::string, 1000> > SortingAlgorithm::getNextStep() {
    return {sortingSteps[++currentStep], namesSortingSteps[currentStep]};
}

std::pair<float*, std::array<std::string, 1000> > SortingAlgorithm::getPreviousStep() {
    return {sortingSteps[--currentStep], namesSortingSteps[currentStep]};
}

bool SortingAlgorithm::areNoStepsRemaining() {
    return currentStep == sortingSteps.size() - 1;
}

bool SortingAlgorithm::isAtStart() {
    return currentStep <= 0;
}

std::pair<float*, std::array<std::string, 1000> > SortingAlgorithm::getSorted() {
    return {sortingSteps[999], namesSortingSteps[999]};
}

float* SortingAlgorithm::copyFloatPointer(float *rhs) {
    int size = 1000;
    float* copy = new float[size];
    for (int i = 0; i < size; i++) {
        copy[i] = rhs[i];
    }
    return copy;
}

void SortingAlgorithm::reset() {
    currentStep = -1;
}
