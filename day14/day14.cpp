/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <string>

void polymerization(unsigned int steps) {
    std::fstream input("input");
    std::string line;

    std::map<unsigned int, uint64_t> pair_counts;
    std::map<unsigned int, char> rules;
    std::map<char, uint64_t> element_counts;
    auto id = [](uint8_t a, uint8_t b){ return a | (b << 8); };

    input >> line;
    for (size_t i = 1; i < line.size(); i++) {
        pair_counts[id(line[i-1], line[i])]++;
    }

    element_counts[line.back()]++; // Last element

    for (std::string dummy, c; input >> line >> dummy >> c; rules[id(line[0], line[1])] = c[0]);

    for (unsigned int i = 0; i < steps; i++) {
        std::map<unsigned int, uint64_t> new_pairs;
        for (auto& pair_count : pair_counts) {
            char new_element = rules[pair_count.first];
            if (new_element) {
                new_pairs[id(pair_count.first & 0xff, new_element)] += pair_count.second;
                new_pairs[id(new_element, (pair_count.first >> 8) & 0xff)] += pair_count.second;
            } else {
                new_pairs[pair_count.first] = pair_count.second;
            }
        }
        pair_counts = new_pairs;
    }

    for (auto& pair_count : pair_counts) {
        element_counts[pair_count.first & 0xff] += pair_count.second;
    }

    uint64_t min = std::numeric_limits<uint64_t>::max(), max = 0;
    for (auto& element : element_counts) {
        min = std::min(min, element.second);
        max = std::max(max, element.second);
    }

    std::cout << (max - min) << std::endl;
}

int main() {
    polymerization(10);
    polymerization(40);
}
