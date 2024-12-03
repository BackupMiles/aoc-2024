#include <regex>
#include <fstream>
#include <iostream>
#include <sstream>

/**
 * Given an input, find a pattern that looks like `mul(xxx,xxx)`, perform a multiplication,
 * add up all the results
 */

std::string clean_line(const std::string& line, const std::regex& dont_regex);
int sum_line_multiplications(const std::string& line, const std::regex& mul_regex);

int main() {
    std::string fileName = "../day-03/input.txt";
    std::ifstream inputFile(fileName);

    if (!inputFile.good()) {
        // error code
        return 1;
    }

    // input is still divided in lines, time for a good ol stream
    std::string line;
    int sum = 0;
    std::regex dont_regex(R"rgx((don\'t\(\).*?)(?=do\(\)|$))rgx");
    std::regex mul_regex(R"rgx(mul\(([0-9]{1,3})\,([0-9]{1,3})\))rgx");

    while (std::getline(inputFile, line)) {
        std::string clean = (clean_line(line, dont_regex));
        sum += sum_line_multiplications(clean, mul_regex);
    }

    inputFile.close();
    std::cout << sum;
}

// remove all the don't-s sequences from the input string
std::string clean_line(const std::string& line, const std::regex& dont_regex) {
    auto mul_begin = std::regex_iterator(line.begin(), line.end(), dont_regex);
    auto mul_end = std::sregex_iterator();

    std::string result(line);

    for (std::regex_iterator i = mul_begin; i != mul_end; i++) {
        std::smatch match = *i;
        std::string as_str = match.str();

        result = std::regex_replace(result, dont_regex, "");
    }

    return result;
}

int sum_line_multiplications(const std::string& line, const std::regex& mul_regex) {
    auto mul_begin = std::regex_iterator(line.begin(), line.end(), mul_regex);
    auto mul_end = std::sregex_iterator();
    int sum = 0;

    for (std::regex_iterator i = mul_begin; i != mul_end; i++) {
        std::smatch match = *i;
        int first = std::stoi(match[1]);
        int second = std::stoi(match[2]);

        sum += first * second;
    }

    return sum;
}