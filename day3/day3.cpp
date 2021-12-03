/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <fstream>
#include <iostream>
#include <string>

#define WIDTH (12)

void part1() {
    std::fstream input("input");
    std::string line;
    unsigned int line_count = 0;
    unsigned int one_counts[WIDTH] = { 0 };

    while (!input.eof()) {
        unsigned int *one_count = one_counts;
        input >> line;

        for(auto c : line) {
            if (c == '1') {
                ++*one_count;
            }
            ++one_count;
        }

        ++line_count;
    }

    unsigned int result = 0;
    for (int i = 0; i < WIDTH; i++) {
        result <<= 1;
        result |= (one_counts[i] * 2 > line_count) ? 1 : 0;
    }
    result *= (~result) & ((1 << WIDTH) - 1);

    std::cout << result << std::endl;
}

void part2() {
    std::fstream input("input");

    std::cout << 0 << std::endl;
}

int main() {
    part1();
    part2();
}
