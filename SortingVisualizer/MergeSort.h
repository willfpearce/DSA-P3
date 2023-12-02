#include "SortingAlgorithm.h"
#pragma once

class MergeSort : public SortingAlgorithm {
private:
	void merge(float* pops, std::array<std::string, 1000> &names, int left, int mid, int right);
	void merge_sort(float* pops, std::array<std::string, 1000> &names, int left, int right);
	void push(std::array<std::string, 1000> names);
public:
	MergeSort(float* pops, std::array<std::string, 1000> &names);
};
