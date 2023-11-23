#include "SortingAlgorithm.h"
#pragma once


// TODO separate into header and source files
class QuickSort : public SortingAlgorithm{ //Class for the Quicksort algorithm
private:
    void Sort(std::array<std::pair<std::string, int>, 1000>& input, int low, int high); //Recursive function that sorts recursively via a quicksort method.
    int Partition(std::array<std::pair<std::string, int>, 1000>& input, int low, int high);
    void Swap(std::array<std::pair<std::string, int>, 1000>& input, int first, int second); //Swaps items in the array
    void Update(std::array<std::pair<std::string, int>, 1000> input); //Updates the current status of the array and adds that as a step.
public:
    explicit QuickSort(std::array<std::pair<std::string, int>, 1000> input); //Constructor for this class, automatically sorts data
};

QuickSort::QuickSort(std::array<std::pair<std::string, int>, 1000> input) {
    Update(input); //Records initial state of array
    Sort(input, 0, 999); //Preforms quick sort
}

void QuickSort::Sort(std::array<std::pair<std::string, int>, 1000>& input, int low, int high) {
    if(low < high){ //Unless the base case of the low integer now exceeding the high, a quick sort pass is conducted and split to be preformed again recursively.
        int pivot = Partition(input, low, high); //Sort pass
        Sort(input, low, pivot - 1); //Recursively sorts lower section
        Sort(input, pivot + 1, high); //Recursively sorts higher section
    }
}

int QuickSort::Partition(std::array<std::pair<std::string, int>, 1000>& input, int low, int high) {
    int pivot = input[low].second;
    int up = low;
    int down = high;
    while(up < down){
        for(int i = up; i < high; i++){ //Increments up until it finds a value greater than the pivot or it has reached the end of this section.
            if(input[up].second > pivot){
                break;
            }
            up++;
        }
        for(int j = high; j > low; j--){ //Decrements down until it finds an element less than the pivot or it has reached the start of this section.
            if(input[down].second < pivot){
                break;
            }
            down--;
        }
        if(up < down){ //Swaps the Up and Down indices if they are out of order.
            Swap(input, up, down);
        }
    }
    Swap(input, low, down); //Swaps the pivot index with the current down index.
    return down;
}

void QuickSort::Swap(std::array<std::pair<std::string, int>, 1000>& input, int first, int second) { //Swaps two indices of the array
    std::pair<std::string, int> temp = input[first];
    input[first] = input[second];
    input[second] = temp;
    Update(input); //Updates the steps vector.
}

void QuickSort::Update(std::array<std::pair<std::string, int>, 1000> input) { //Creates a copy of the current state of the data being sorted and adds it to the steps.
    sortingSteps.push_back(input);
}