#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <optional>

/**
 * Given a matrix, find how many times "XMAS" appears by comparing it to its neighbors
 */

int visit_neighbors(
    int target_idx, 
    const std::vector<int>& coordinates,
    const std::optional<std::vector<int>>& direction,
    const std::vector<std::vector<char>>& matrix
);
bool is_direction_valid(const std::vector<int>& direction, const std::vector<int>& coordinates, int matrix_size);
const std::vector<int>& calculate_next_coordinates(const std::vector<int>& direction, const std::vector<int>& coordinates);

const std::string& TARGET = "XMAS";
const std::vector<std::vector<int>>& DIRECTIONS = {
    { -1, -1 }, { -1, 0 }, { -1, 1 },
    { 0, -1 }, { 0, 1 },
    { 1, -1 }, { 1, 0 }, { 1, 1 }
};

int main() {
    std::ifstream file("../day-04/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    std::vector<std::vector<char>> matrix;
    std::optional<std::vector<int>> direction;
    std::string line;
    int count;

    while (std::getline(file, line)) {
        // convert the line into a vector of characters
        std::vector<char> row;
        for (int i = 0; i < line.size(); i++) {
            row.push_back(line[i]);
        }
        matrix.push_back(row);
    }

    file.close();

    // y = depth, row
    for (int y = 0; y < matrix.size(); y++) {
        // x = width, column
        for (int x = 0; x < matrix[y].size(); x++) {
            count += visit_neighbors(0, std::vector<int>{ y, x }, direction, matrix);
        }
    }

    std::cout << count << std::endl;
    return 0;
}

int visit_neighbors(
    int target_idx, 
    const std::vector<int>& coordinates,
    const std::optional<std::vector<int>>& direction,
    const std::vector<std::vector<char>>& matrix
) {
    int result = 0;
    if (!direction.has_value()) {
        for (int i = 0; i < DIRECTIONS.size(); i++) {
            auto current_direction = DIRECTIONS[i];
            if (!is_direction_valid(current_direction, coordinates, matrix.size())) {
                continue;
            }

            result += visit_neighbors(target_idx, coordinates, current_direction, matrix);
        }
        return result;
    }


    char examinee = matrix[coordinates[1]][coordinates[0]];

    if (examinee == TARGET[target_idx]) {
        if (target_idx == TARGET.size() - 1) {
            result += 1;
            return result;
        }

        int new_y = coordinates[0] + direction.value()[ 0 ];
        int new_x = coordinates[1] + direction.value()[1];

        result += visit_neighbors(target_idx + 1, std::vector<int>{ new_y, new_x }, direction, matrix);
    }

    return result;
}

// check whether target might appear in the direction
bool is_direction_valid(const std::vector<int>& direction, const std::vector<int>& coordinates, int matrix_size) {
    int row = coordinates[0] + direction[0] * (TARGET.size() - 1);
    bool is_x_valid = row >= 0 && row < matrix_size;
    if (!is_x_valid) return false;
    
    int column = coordinates[1] + direction[1] * (TARGET.size() - 1);
    bool is_y_valid = column >= 0 && column < matrix_size;
    if (!is_y_valid) return false;

    return true;
}
