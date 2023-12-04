#include "ShellSort.h"


// swap values and add changed array to sortingSteps vector
void ShellSort::swap(float* pops, size_t i, size_t j) {
    swapCount++;
    auto temp = pops[i];
    pops[i] = pops[j];
    pops[j] = temp;
    auto copy = copyFloatPointer(pops);
    sortingSteps.push_back(copy);
}

// swap for names array
void ShellSort::swap(std::array<std::string, 1000> names, size_t i, size_t j) {
    auto temp = names[i];
    names[i] = names[j];
    names[j] = temp;
    auto copy = names;
    namesSortingSteps.push_back(copy);
}

// Shell sort algorithm based on textbook implementation
void ShellSort::modifiedInsSort(float* pops, std::array<std::string, 1000> names, size_t start, size_t incr) {
    size_t size = 1000;
    for (size_t i = start+incr; i < size; i += incr)
        for (size_t j = i; ((j >= incr) && (pops[j] < pops[j - incr])); j -= incr) {
            swap(pops, j, j - incr);
            swap(names, j, j - incr);
        }
}

// sorting is completed in the constructor so that the interacting with the class object allows
// the user to analyze aspects of the algorithm
ShellSort::ShellSort(float* pops, std::array<std::string, 1000> names) {
    // measuring time of sort
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    auto copy = copyFloatPointer(pops);
    // here we add all sorting intermediate steps to this vector to be used in the visualization
    sortingSteps.push_back(copy);

    size_t size = 1000;
    for (size_t i = size/2; i > 2; i /= 2.2)  // For each increment
        for (size_t j = 0; j < i; j++)  // Sort each sublist
            modifiedInsSort(pops, names, j, i);
    modifiedInsSort(pops, names, 0, 1);

    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
    sortTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}
