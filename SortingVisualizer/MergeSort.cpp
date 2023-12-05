#include "MergeSort.h"

void MergeSort::merge(float* pops, std::array<std::string, 1000> &names, int left, int mid, int right) {
	int arr_1 = mid - left + 1;
	int arr_2 = right - mid;

	// create two subarrays
	std::array<std::pair<std::string, int>, 1000> left_arr;
	std::array<std::pair<std::string, int>, 1000> right_arr;

	// copy data to the subarrays
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
		// compares the population number of the subarrays
		if (left_arr[index_arr_1].second <= right_arr[index_arr_2].second) {
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
		++swapCount;
	}

	// copy any elements left, if there are any
	while (index_arr_1 < arr_1) {
		names[index_merged_arr] = left_arr[index_arr_1].first;
		pops[index_merged_arr] = left_arr[index_arr_1].second;
		++index_arr_1;
		++index_merged_arr;
		++swapCount;
	}

	while (index_arr_2 < arr_2) {
		names[index_merged_arr] = right_arr[index_arr_2].first;
		pops[index_merged_arr] = right_arr[index_arr_2].second;
		++index_arr_2;
		++index_merged_arr;
		++swapCount;
	}

	// push the copy of each change after the merge for the visualization purposes
	auto copy = copyFloatPointer(pops);
	sortingSteps.push_back(copy);
	auto copy_2 = names;
	namesSortingSteps.push_back(copy_2);
	
}

void MergeSort::merge_sort(float* pops, std::array<std::string, 1000> &names, int left, int right) {
	// condition to check whether the parameters are valid
	if (left < right) {
		int mid = left + (right - left) / 2;
		merge_sort(pops, names, left, mid);
		merge_sort(pops, names, mid + 1, right);
		merge(pops, names, left, mid, right);
	}
}

MergeSort::MergeSort(float* pops, std::array<std::string, 1000> &names) {
	// push the initial unordered copy of the input (sortingSteps and namesSortingSteps are class member variables of the SortingAlgorithm class)
	auto copy = copyFloatPointer(pops);
	sortingSteps.push_back(copy);
	auto copy_2 = names;
	namesSortingSteps.push_back(copy_2);
	// used to track the time it takes for the algorithm to fully sort the input
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	merge_sort(pops, names, 0, 999);
	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
	// class member variable of the SortingAlgorithm class
	sortTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

