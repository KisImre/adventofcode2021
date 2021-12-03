/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <fstream>
#include <iostream>

int main() {
    int prev = 0;
    int current = 0;
    unsigned int count = 0;

    std::fstream input("input");

    input >> prev;
    while(!input.eof()) {
        input >> current;
        if (current > prev)
            ++count;
        prev = current;
    }

    std::cout << count << std::endl;
}
