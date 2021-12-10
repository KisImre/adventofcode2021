/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>

std::map<char, char> pairs = {{'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};
std::map<char, unsigned int> scores = {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
std::map<char, unsigned int> autocomplete_scores = {{'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}};

int main() {
    std::fstream input("input");
    std::string line;

    unsigned int result = 0;
    std::vector<uint64_t> autocomplete_result;
    while (input >> line) {
        std::list<char> stack;
        bool valid = true;
        for (auto c : line) {
            if (pairs.find(c) != pairs.end()) {
                stack.push_back(c);
            } else if (c == pairs[stack.back()]) {
                stack.pop_back();
            } else {
                // Error
                result += scores[c];
                valid = false;
                break;
            }
        }

        if (valid) {
            uint64_t autocomplete_score = 0;
            for (auto it = stack.rbegin(); it != stack.rend(); it++) {
                autocomplete_score *= 5;
                autocomplete_score += autocomplete_scores[*it];
            }
            autocomplete_result.push_back(autocomplete_score);
        }
    }

    std::sort(autocomplete_result.begin(), autocomplete_result.end());

    std::cout << result << std::endl;
    std::cout << autocomplete_result[autocomplete_result.size() / 2] << std::endl;
}

