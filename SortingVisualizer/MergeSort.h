#include "SortingAlgorithm.h"
#pragma once

class MergeSort : public SortingAlgorithm {
private:
	void merge(float* pops, std::array<std::string, 1000> &names, int left, int mid, int right); // merging the subarrays (helper function)
	void merge_sort(float* pops, std::array<std::string, 1000> &names, int left, int right); // the algorithm itself
public:
	MergeSort(float* pops, std::array<std::string, 1000> &names); // constructor that ties the algorithm to the structure of the project
};
