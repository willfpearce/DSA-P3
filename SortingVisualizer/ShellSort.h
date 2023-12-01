#include "SortingAlgorithm.h"
#pragma once

class ShellSort : public SortingAlgorithm {
private:
    void swap(float* pops, size_t i, size_t j);
    void swap(std::array<std::string, 1000> names, size_t i, size_t j);
    void modifiedInsSort(float* pops, std::array<std::string, 1000> names, size_t start, size_t incr);
public:
    ShellSort(float* pops, std::array<std::string, 1000> names);

};