#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>

/**
 * Given a list of numbers with two columns, for each row, figure out the difference
 * between the two, output the sum of this operation
 */

// forward declaration for increased swaggery
void populate_lists(const std::string& line, std::vector<int>& lefties, std::vector<int>& righties);
void sort_list(std::vector<int>& list);

int main() {
    std::string fileName = "../day-01/input.txt";
    std::ifstream inputFile(fileName);

    if (!inputFile.good()) {
        std::cerr << "Error: could not open file " << fileName;
        // error code
        return 1;
    }

    std::string line;
    int sum = 0;
    std::vector<int> lefties;
    std::vector<int> righties;
    
    while (std::getline(inputFile, line)) {
        populate_lists(line, lefties, righties);
    }

    if (lefties.size() != righties.size()) {
        std::cerr << lefties.size() << " , " << righties.size();
        return 1;
    }

    sort_list(lefties);
    sort_list(righties);

    for (int i = 0; i < lefties.size(); i++) {
        sum += abs(lefties[i] - righties[i]);
    }

    inputFile.close();

    std::cout << sum;
    // success
    return 0;
}

void populate_lists(const std::string& line, std::vector<int>& lefties, std::vector<int>& righties) {
    std::istringstream stream (line);
    int parsed_number;
    int idx = 0;

    while (stream >> parsed_number && idx < 2) {
        if (idx == 0) {
            lefties.push_back(parsed_number);
            idx++;
            continue;
        }
        righties.push_back(parsed_number);
    }
}

void sort_list(std::vector<int>& list) {
    std::sort(list.begin(), list.end(), [](int a, int b) {
        return a < b;
    });
}