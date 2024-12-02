#include <optional>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

/**
 * Given a matrix, for each row find out whether it is "safe" or not
 * - safe: true if all numbers are either increasing or decreasing by a distance of 3 at most
 */

int calculate_report_safety(const std::string& line, int line_idx);
bool verify_report_validity(std::vector<int>& report, bool has_run);

int main() {
    std::string fileName = "../day-02/input.txt";
    std::ifstream inputFile(fileName);
    int line_idx = 1;

    if (!inputFile.good()) {
        // error code
        return 1;
    }

    std::string line;
    int total_safe_reports = 0;
    while (std::getline(inputFile, line)) {
        total_safe_reports += calculate_report_safety(line, line_idx);
        line_idx++;
    }

    inputFile.close();

    std::cout << total_safe_reports;
}

int calculate_report_safety(const std::string& line, int line_idx) {
    std::istringstream stream (line);
    int parsed_number;

    // true = asc, false = desc
    std::vector<int> report;

    while (stream >> parsed_number) {
        report.push_back(parsed_number);
    }

    bool is_valid = verify_report_validity(report, false);

    return is_valid ? 1 : 0;
}

bool verify_report_validity(std::vector<int>& report, bool has_run) {
    int previous = -1;
    std::optional<bool> direction;
    
    for (int idx = 0; idx < report.size(); idx++) {
        int parsed_number = report[idx];
        if (idx == 0) {
            previous = parsed_number;
            continue;
        }

        bool is_asc = parsed_number > previous;

        // handle direction switcheroo
        bool has_switched = direction.has_value() && is_asc != *direction;

        // too far off
        bool is_exceeding = abs(parsed_number - previous) > 3 || parsed_number == previous;

        if (has_switched || is_exceeding) {
            if (!has_run) {
                // unoptimal, but ¯\_(ツ)_/¯
                for (int j = 0; j < report.size(); j++) {
                    std::vector<int> failsafe(report);
                    failsafe.erase(failsafe.begin() + j);
                    bool result = verify_report_validity(failsafe, true);
                    if (result) {
                        return true;
                    }
                }
                return false;
            }

            return false;
        }

        direction = is_asc;
        previous = parsed_number;
    }
    return true;
}