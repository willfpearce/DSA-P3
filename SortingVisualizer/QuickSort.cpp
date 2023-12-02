#include "QuickSort.h"

//Sorting code structure borrowed from module 6 lecture slides

QuickSort::QuickSort(float* input, std::array<std::string, 1000> names) {
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    Update(input, names); //Records initial state of array
    Sort(input, names, 0, 999); //Preforms quick sort
    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
    sortTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

void QuickSort::Sort(float *input, std::array<std::string, 1000> &names, int low, int high) {
    if(low < high){ //Unless the base case of the low integer now exceeding the high, a quick sort pass is conducted and split to be preformed again recursively.
        int pivot = Partition(input, names, low, high); //Sort pass
        Sort(input, names, low, pivot - 1); //Recursively sorts lower section
        Sort(input, names, pivot + 1, high); //Recursively sorts higher section
    }
}

int QuickSort::Partition(float* input, std::array<std::string, 1000> &names, int low, int high) {
    float pivot = input[low];
    int up = low;
    int down = high;
    while(up < down){
        for(int i = up; i < high; i++){ //Increments up until it finds a value greater than the pivot, or it has reached the end of this section.
            if(input[up] > pivot){
                break;
            }
            up++;
        }
        for(int j = high; j > low; j--){ //Decrements down until it finds an element less than the pivot, or it has reached the start of this section.
            if(input[down] < pivot){
                break;
            }
            down--;
        }
        if(up < down){ //Swaps the Up and Down indices if they are out of order.
            Swap(input, names, up, down);
        }
    }
    Swap(input, names, low, down); //Swaps the pivot index with the current down index.
    return down;
}

void QuickSort::Swap(float* input, std::array<std::string, 1000> &names, int first, int second) { //Swaps two indices of the array
    swapCount++;
    float temp = input[first];
    std::string tempStr = names[first];
    input[first] = input[second];
    input[second] = temp;
    names[first] = names[second];
    names[second] = tempStr;
    Update(input, names); //Updates the steps vector.
}

void QuickSort::Update(float* input, const std::array<std::string, 1000>& names) { //Creates a copy of the current state of the data being sorted and adds it to the steps.
    sortingSteps.push_back(copyFloatPointer(input));
    namesSortingSteps.push_back(names);
}