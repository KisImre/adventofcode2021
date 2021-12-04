/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

#define WIDTH (12)

typedef std::bitset<WIDTH> bit_value;
typedef std::list<bit_value> bit_value_list;
typedef bit_value_list::iterator bit_value_iterator;

bool most_common_bit(bit_value_iterator begin, bit_value_iterator end, unsigned int position) {
    return std::count_if(begin, end, [&](auto b) { return b[position]; }) * 2 >= std::distance(begin, end);
}

void part1() {
    std::fstream input("input");
    std::string line;
    bit_value_list bits;

    while (!input.eof()) {
        input >> line;
        bits.push_back(bit_value(line));
    }

    bit_value result;
    for (int i = 0; i < WIDTH; i++) {
        result[i] = most_common_bit(bits.begin(), bits.end(), i);
    }

    std::cout << (result.to_ulong() * (~result).to_ulong()) << std::endl;
}

unsigned int find_value(bit_value_list bits, bool least_common) {
    bit_value pattern;
    bit_value mask = 1 << (WIDTH - 1);
    bit_value_iterator end = bits.end();

    for (int i = WIDTH - 1; i >= 0; i--) {
        pattern[i] = most_common_bit(bits.begin(), end, i) ^ least_common;
        end = std::remove_if(bits.begin(), end, [&](auto b) { return ((b ^ pattern) & mask).any(); });
        if (std::distance(bits.begin(), end) == 0) {
            pattern = *bits.begin();
        }
        mask >>= 1;
        mask |= 1 << (WIDTH - 1);
    }

    return pattern.to_ulong();
}

void part2() {
    std::fstream input("input");
    std::string line;
    bit_value_list bits;

    while (!input.eof()) {
        input >> line;
        bits.push_back(bit_value(line));
    }

    unsigned int oxygen = find_value(bits, false);
    unsigned int co2 = find_value(bits, true);

    std::cout << std::dec << oxygen * co2 << std::endl;
}

int main() {
    part1();
    part2();
}
