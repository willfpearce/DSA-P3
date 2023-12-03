#include "QuickSort.h"

//Sorting code structure borrowed from module 6 lecture slides.

QuickSort::QuickSort(float* input, std::array<std::string, 1000> names) {
    Update(input, names); //Records initial state of array.
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now(); //Records starting time.
    Sort(input, names, 0, 999); //Preforms quick sort.
    std::chrono::system_clock::time_point end = std::chrono::system_clock::now(); //Records finishing time.
    sortTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); //Records the duration the sorting took to complete.
}

void QuickSort::Sort(float *input, std::array<std::string, 1000> &names, int low, int high) {
    if(low < high){ //Unless the base case of the low integer now exceeding the high, a quick sort pass is conducted and split to be preformed again recursively.
        int pivot = Partition(input, names, low, high); //Sort pass.
        Sort(input, names, low, pivot - 1); //Recursively sorts lower section.
        Sort(input, names, pivot + 1, high); //Recursively sorts higher section.
    }
}

int QuickSort::Partition(float* input, std::array<std::string, 1000> &names, int low, int high) {
    float pivot = input[low]; //Initializes the pivot value to the first value of this section.
    int up = low; //Initializes the up index to the start of this section.
    int down = high; //Initializes the down index to the end of this section.
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

void QuickSort::Swap(float* input, std::array<std::string, 1000> &names, int first, int second) { //Swaps two indices of the array.
    swapCount++; //Increments the number of swaps preformed.
    float temp = input[first]; //Stores a temporary float for swapping.
    std::string tempStr = names[first]; //Stores a temporary string for swapping.
    input[first] = input[second]; //Swaps populations.
    input[second] = temp;
    names[first] = names[second]; //Swaps city names.
    names[second] = tempStr;
    Update(input, names); //Updates the soring steps vectors so the data at this point in time can be recorded.
}

void QuickSort::Update(float* input, const std::array<std::string, 1000>& names) { //Creates a copy of the current state of the data being sorted and adds it to the steps.
    sortingSteps.push_back(copyFloatPointer(input));
    namesSortingSteps.push_back(names);
}