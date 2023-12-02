#include "SortingAlgorithm.h"
#pragma once

class MergeSort : public SortingAlgorithm {
private:
	void merge(float* pops, std::array<std::string, 1000> &names, int left, int mid, int right);
	void merge_sort(float* pops, std::array<std::string, 1000> &names, int left, int right);
public:
	MergeSort(float* pops, std::array<std::string, 1000> &names) {
		auto copy = copyFloatPointer(pops);
		sortingSteps.push_back(copy);
		namesSortingSteps.push_back(names);
		merge_sort(pops, names, 0, 999);
	}
};
