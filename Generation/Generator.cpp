#include <algorithm>
#include <string>
#include <random>
#include <fstream>
#include <set>
//https://github.com/dwyl/english-words where word data was pulled from.

std::string getLineFromFile(const std::string& filename, int lineNumber) { //Gets a specific line from file (need a specific one because we want a random line and not in order).
    std::ifstream file(filename);
    if (!file.is_open()) {
        exit(EXIT_FAILURE);
    }
    std::string line;
    for (int i = 1; i <= lineNumber; ++i) {
        if (!std::getline(file, line)) {
            exit(EXIT_FAILURE);
        }
    }
    file.close();
    return line;
}

void createAndWriteToFile(const std::string& filename, const std::string& content) { //creates a new file.
    std::ofstream file(filename);
    if (!file.is_open()) {
        exit(EXIT_FAILURE);
    }
    file << content;
    file.close();
}


std::random_device rd;
std::mt19937 gen(rd());

int getRandom(int low, int high){ //returns a random number
    std::uniform_int_distribution<int> distribution(low, high);
    return distribution(gen);
}

int main(){ //Generates data
    for(int j = 1; j <= 50; j++) {
        std::string title = getLineFromFile("States.txt", j);
        std::string out = "";
        std::set<int> used;
        for (int i = 0; i < 1000; i++) { //generates 1000 random populations for the state
            int rand = getRandom(10000, 1000000);
            out += (std::to_string(rand) + "\n");
        }
        for (int i = 0; i < 1000; i++) { //generates 1000 random names for the state
            int rand = getRandom(1, 460000);
            if (used.emplace(rand).second) {
                std::string name = getLineFromFile("words.txt", rand);
                out += (name + "ville" + "\n");
            } else {
                i--; //makes this take a long time to run, but we only used this file once, and it ensures  there are no repeat names.
            }
        }
        createAndWriteToFile(title + ".txt", out);
    }
    return 0;
}