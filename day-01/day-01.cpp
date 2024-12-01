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
int calculate_similarity(std::vector<int>& lefties, std::vector<int>& righties);
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

    // part 2
    int similarity_score = calculate_similarity(lefties, righties);
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Similarity score: " << similarity_score << std::endl;

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

int calculate_similarity(std::vector<int>& lefties, std::vector<int>& righties) {
    int sum = 0;

    for (int i = 0; i < lefties.size(); i++) {
        int current_left = lefties[i];
        int counter = 0;

        for (int j = 0; j < righties.size(); j++) {
            int current_right = righties[j];

            // cannot possibly get it
            if (current_right > current_left) {
                break;
            }
            if (current_right == current_left) {
                counter++;
            }
        }

        sum += current_left * counter;
    }

    return sum;
}