#include "SortingAlgorithm.h"
#pragma once

class MergeSort : public SortingAlgorithm {
private:
	void merge(std::array<std::pair<std::string, int>, 1000> &arr, int left, int mid, int right);
	void merge_sort(std::array<std::pair<std::string, int>, 1000> &arr, int left, int right);
public:
	MergeSort(std::array<std::pair<std::string, int>, 1000> &arr) {
		sortingSteps.push_back(arr);
		merge_sort(arr, 0, 999);
	}
};

void MergeSort::merge(std::array<std::pair<std::string, int>, 1000> &arr, int left, int mid, int right) {
	int arr_1 = mid - left + 1;
	int arr_2 = right - mid;
	
	std::pair<std::string, int> left_arr[arr_1];
	std::pair<std::string, int> right_arr[arr_2];
	
	for (int i = 0; i < arr_1; ++i) {
		left_arr[i] = arr[left + i];
	}

	for (int j = 0; j < arr_2; ++j) {
		right_arr[j] = arr[mid + j + 1];
	}

	int index_arr_1 = 0;
	int index_arr_2 = 0;
	int index_merged_arr = left;

	while (index_arr_1 < arr_1 && index_arr_2 < arr_2) {
		if (left_arr[index_arr_1] <= right_arr[index_arr_2]) {
			arr[index_merged_arr] = left_arr[index_arr_1];
			++index_arr_1;
		}
		else {
			arr[index_merged_arr] = right_arr[index_arr_2];
			++index_arr_2;;
		}
		++index_merged_arr;
	}
	
	while (index_arr_1 < arr_1) {
		arr[index_merged_arr] = left_arr[index_arr_1];
		++index_arr_1;
		++index_merged_arr;
	}

	while (index_arr_2 < arr_2) {
		arr[index_merged_arr] = right_arr[index_arr_2];
		++index_arr_2;
		++index_merged_arr;
	}


	sortingSteps.push_back(arr);
	
}

void MergeSort::merge_sort(std::array<std::pair<std::string, int>, 1000> &arr, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}
