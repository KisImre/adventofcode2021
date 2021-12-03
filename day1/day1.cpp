/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <fstream>
#include <iostream>

template<typename T, size_t size>
class CompareWindow {
    public:
        void readItem(std::fstream &stream) {
            stream >> buffer[index++];
            index %= size;
        }
        bool increased() {
            return buffer[index] < buffer[(index + size - 1) % size];
        }

    private:
        T buffer[size] = { 0 };
        size_t index = 0;
};

void part1() {
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

void part2() {
    CompareWindow<int, 4> window;
    unsigned int count = 0;

    std::fstream input("input");

    window.readItem(input);
    window.readItem(input);
    window.readItem(input);

    while(!input.eof()) {
        window.readItem(input);
        count += window.increased();
    }

    std::cout << count << std::endl;
}

int main() {
    part1();
    part2();
}