#include "MergeSort.h"

void MergeSort::merge(float* pops, std::array<std::string, 1000> &names, int left, int mid, int right) {
	int arr_1 = mid - left + 1;
	int arr_2 = right - mid;
	
	std::array<std::pair<std::string, int>, 1000> left_arr;
	std::array<std::pair<std::string, int>, 1000> right_arr;
	
	for (int i = 0; i < arr_1; ++i) {
		left_arr[i].first = names[left + i];
		left_arr[i].second = pops[left + i];
	}

	for (int j = 0; j < arr_2; ++j) {
		right_arr[j].first = names[mid + j + 1];
		right_arr[j].second = pops[mid + j + 1];
	}

	int index_arr_1 = 0;
	int index_arr_2 = 0;
	int index_merged_arr = left;

	while (index_arr_1 < arr_1 && index_arr_2 < arr_2) {
		if (left_arr[index_arr_1] <= right_arr[index_arr_2]) {
			names[index_merged_arr] = left_arr[index_arr_1].first;
			pops[index_merged_arr] = left_arr[index_arr_1].second;
			++index_arr_1;
		}
		else {
			names[index_merged_arr] = right_arr[index_arr_2].first;
			pops[index_merged_arr] = right_arr[index_arr_2].second;
			++index_arr_2;;
		}
		++index_merged_arr;
	}
	
	while (index_arr_1 < arr_1) {
		names[index_merged_arr] = left_arr[index_arr_1].first;
		pops[index_merged_arr] = left_arr[index_arr_1].second;
		++index_arr_1;
		++index_merged_arr;
	}

	while (index_arr_2 < arr_2) {
		names[index_merged_arr] = right_arr[index_arr_2].first;
		pops[index_merged_arr] = right_arr[index_arr_2].second;
		++index_arr_2;
		++index_merged_arr;
	}

	
	auto copy = copyFloatPointer(pops);
	sortingSteps.push_back(copy);
	
}

void MergeSort::merge_sort(float* pops, std::array<std::string, 1000> &names, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		merge_sort(pops, names, left, mid);
		merge_sort(pops, names, mid + 1, right);
		merge(pops, names, left, mid, right);
	}
}

