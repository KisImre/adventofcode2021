/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <cstdint>
#include <deque>
#include <fstream>
#include <iostream>

void calculate_fish(unsigned int rounds) {
    std::fstream input("input");
    std::deque<uint64_t> fish(9, 0);
    unsigned int temp = 0;
    char c = '\0';

    while (!input.eof()) {
        input >> temp >> c;
        ++fish[temp];
    }

    for (unsigned int i = 0; i < rounds; i++) {
        fish.push_back(fish.front());
        fish.pop_front();
        fish[6] += fish.back();
    }

    uint64_t count = 0;
    for (int i = 0; i < 9; i++) {
        count += fish[i];
    }

    std::cout << count << std::endl;
}

int main() {
    calculate_fish(80);
    calculate_fish(256);
}
