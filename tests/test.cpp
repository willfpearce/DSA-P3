#include "../SortingVisualizer/QuickSort.h"
#include "../SortingVisualizer/ShellSort.h"
//#include "../SortingVisualizer/MergeSort.h"
#include <random>
#include <algorithm>
#include <iostream>

#define SIZE 1000


std::random_device rd;
std::mt19937 gen(rd());

int getRandom(int low, int high){
    std::uniform_int_distribution<int> distribution(low, high);
    return distribution(gen);
}

std::array<std::pair<std::string, int>, SIZE> generateData(){
    std::array<std::pair<std::string, int>, SIZE> data;
    for(int i = 0; i < SIZE; i++){
        data[i] = std::make_pair("", getRandom(1, 10000));
    }
    return data;
};

bool compareSecondInPair(std::pair<std::string, int>& pair1, std::pair<std::string, int>& pair2) {
    return pair1.second < pair2.second;
}

void test(std::string testName, std::array<std::pair<std::string, int>, SIZE> testArray, std::array<std::pair<std::string, int>, SIZE> controlArray) {
    bool isSame = testArray == controlArray;
    if (isSame) {
        std::cout << "Test: " << testName << " was successful. TestArray == ControlArray" <<std::endl;
    } else {
        std::cout << "Test: " << testName << " has failed. TestArray != ControlArray" << std::endl;
    }
}

int main() {
    std::array<std::pair<std::string, int>, SIZE> randomData = generateData();
    auto sortedRandomData = randomData;
    std::sort(sortedRandomData.begin(), sortedRandomData.end(), compareSecondInPair);

    QuickSort qs(randomData);
    ShellSort ss(randomData);
//    MergeSort ms(randomData);

    test("QuickSort", qs.getSorted(), sortedRandomData);
    test("ShellSort", ss.getSorted(), sortedRandomData);

}
