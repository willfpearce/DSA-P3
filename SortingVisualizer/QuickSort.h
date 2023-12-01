#include "SortingAlgorithm.h"
#pragma once


class QuickSort : public SortingAlgorithm{ //Class for the Quicksort algorithm
private:
    void Sort(float* input, std::array<std::string, 1000>& names, int low, int high,); //Recursive function that sorts recursively via a quicksort method.
    int Partition(float* input, std::array<std::string, 1000> &names, int low, int high);
    void Swap(float* input, std::array<std::string, 1000> &names, int first, int second); //Swaps items in the array
    void Update(float input[1000], const std::array<std::string, 1000>& names); //Updates the current status of the array and adds that as a step.
public:
    explicit QuickSort(float input[1000], std::array<std::string, 1000>); //Constructor for this class, automatically sorts data
};
