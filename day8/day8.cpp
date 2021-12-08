/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::map<char, char> create_map(const std::map<char, unsigned int> &hashes) {
    std::map<unsigned int, char> lut = {{567000, 'a'}, {30240, 'b'}, {151200, 'c'}, {126000, 'd'}, {1260, 'e'}, {907200, 'f'}, {189000, 'g'}};
    std::map<char, char> map;
    std::for_each(hashes.begin(), hashes.end(), [&](auto &hash){ map[hash.first] = lut[hash.second]; });
    return map;
}

unsigned int decode(std::map<char, char> &map, std::string digit) {
    std::vector<std::string> lut = { "abcefg", "cf", "acdeg", "acdfg", "bcdf", "abdfg", "abdefg", "acf", "abcdefg", "abcdfg" };
    std::for_each(digit.begin(), digit.end(), [&](auto &c){ c = map[c]; });
    std::sort(digit.begin(), digit.end());
    return std::distance(lut.begin(), std::find(lut.begin(), lut.end(), digit));
}

void part1() {
    std::fstream input("input");
    std::string entry;

    unsigned int count = 0;
    while (!input.eof()) {
        for (int i = 0; i < 11; i++) input >> entry;
        for (int i = 0; i < 4; i++) {
            input >> entry;
            unsigned len = entry.length();
            if (len == 2 || len == 3 || len == 4 || len == 7) ++count;
        }
    }

    std::cout << count << std::endl;
}

void part2() {
    std::fstream input("input");
    std::string entry;

    unsigned int sum = 0;
    while (!input.eof()) {
        std::map<char, unsigned int> hashes = {{'a', 1}, {'b', 1}, {'c', 1}, {'d', 1}, {'e', 1}, {'f', 1}, {'g', 1}};

        for (int i = 0; i < 10; i++) {
            input >> entry;
            std::for_each(entry.begin(), entry.end(), [&](auto c) {hashes[c] *= entry.length();});
        }

        input >> entry; // |

        std::map<char, char> map = create_map(hashes);
        unsigned int res = 0;
        for (int i = 0; i < 4; i++) {
            input >> entry;
            res *= 10;
            res += decode(map, entry);
        }
        sum += res;
    }

    std::cout << sum << std::endl;
}

int main() {
    part1();
    part2();
}
