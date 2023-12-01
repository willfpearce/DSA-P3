#include "SortingAlgorithm.h"

float* SortingAlgorithm::getNextStep() {
    return sortingSteps[++currentStep];
}

float* SortingAlgorithm::getPreviousStep() {
    return sortingSteps[--currentStep];
}

bool SortingAlgorithm::areNoStepsRemaining() {
    return currentStep == sortingSteps.size() - 1;
}

float* SortingAlgorithm::getSorted() {
    return sortingSteps.back();
}

float* SortingAlgorithm::copyFloatPointer(float *rhs) {
    int size = 1000;
    float* copy = new float[size];
    for (int i = 0; i < size; i++) {
        copy[i] = rhs[i];
    }
}