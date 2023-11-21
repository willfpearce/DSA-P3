#include "ShellSort.h"


// swap values and add changed array to sortingSteps vector
void ShellSort::swap(std::array<std::pair<std::string, int>, 1000>& arr, size_t i, size_t j) {
    auto temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    auto copy = arr;
    sortingSteps.push_back(copy);
}

// Shell sort algorithm based on textbook implementation
void ShellSort::modifiedInsSort(std::array<std::pair<std::string, int>, 1000>& arr, size_t start, size_t incr) {
    size_t size = 1000;
    for (size_t i = start+incr; i < size; i += incr)
        for (size_t j = i; ((j >= incr) && (arr[j].second < arr[j-incr].second)); j -= incr)
            swap(arr, j, j-incr);
}

// TODO: passed by ref, subject to change
ShellSort::ShellSort(std::array<std::pair<std::string, int>, 1000> arr) {
    auto copy = arr;
    sortingSteps.push_back(copy);

    size_t size = 1000;
    for (size_t i = size/2; i > 2; i /= 2.2)  //For each increment
        for (size_t j = 0; j < i; j++)  //Sort each sublist
            modifiedInsSort(arr, j, i);
    modifiedInsSort(arr, 0, 1);
}
