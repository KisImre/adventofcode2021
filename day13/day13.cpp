/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#define SIZE    (2048)

bool map[SIZE][SIZE] = { 0 };

void fold(char axis, unsigned int param) {
    unsigned int width = param * 2;
    unsigned int x_start = (axis == 'x') ? param + 1 : 0;
    unsigned int y_start = (axis == 'y') ? param + 1 : 0;

    for (unsigned int x = x_start; x < SIZE; x++) {
        for (unsigned int y = y_start; y < SIZE; y++) {
            if (map[x][y]) {
                ((axis == 'x') ? map[width - x][y] : map[x][width - y]) = true;
                map[x][y] = false;
            }
        }
    }
}

unsigned int count_covered() {
    unsigned int sum = 0;

    for (unsigned int x = 0; x < SIZE; x++) {
        for (unsigned int y = 0; y < SIZE; y++) {
            sum += map[x][y];
        }
    }

    return sum;
}

void print() {
    for (unsigned int y = 0; y < 6; y++) {
        for(unsigned int x = 0; x < 50; x++) {
            std::cout << (map[x][y] ? "#" : ".");
        }
        std::cout  << std::endl;
    }
}

int main() {
    std::fstream input("input");
    char dummy = 0;
    unsigned int first_count = 0;

    for (unsigned int x = 0, y = 0; input >> x >> dummy >> y; map[x][y] = true);

    input.clear();
    for (std::string line; input >> line; ){
        std::istringstream line_stream(line);
        char axis = 0;
        unsigned int fold_position = 0;

        if (line_stream >> axis >> dummy >> fold_position) {
            fold(axis, fold_position);
            first_count = (first_count == 0) ? count_covered() : first_count;
        }
    }

    std::cout << first_count << std::endl;
    print();
}
