#include "SortingAlgorithm.h"
#pragma once

class ShellSort : public SortingAlgorithm {
private:
    void swap(std::array<std::pair<std::string, int>, 1000>& arr, size_t i, size_t j);
    void modifiedInsSort(std::array<std::pair<std::string, int>, 1000> &arr, size_t start, size_t incr);
public:
    ShellSort(std::array<std::pair<std::string, int>, 1000>);

};