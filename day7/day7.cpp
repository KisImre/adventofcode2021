/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>

typedef unsigned int (*distance_function)(unsigned int test_pos, unsigned int pos);

void solve(bool x) {
    std::fstream input("input");
    std::map<unsigned int, unsigned int> crabs;
    unsigned int temp = 0;
    char c = '\0';

    while (!input.eof()) {
        input >> temp >> c;
        ++crabs[temp];
    }

    auto linear = [](unsigned int test_pos, unsigned int pos) { return abs(test_pos - pos); };
    auto squared = [](unsigned int test_pos, unsigned int pos) { unsigned int n = abs(test_pos - pos); return n * (n + 1) / 2; };

    unsigned int min_fuel = std::numeric_limits<unsigned int>::max();
    for (unsigned int i = 0; i < crabs.rbegin()->first; i++) {
        auto sum = [&](auto s, auto &c){ return s + ((x) ? squared(i, c.first) : linear(i, c.first)) * c.second; };
        min_fuel = std::min(min_fuel, (unsigned int)std::accumulate(crabs.begin(), crabs.end(), 0, sum));
    }

    std::cout << min_fuel << std::endl;
}

int main() {
    solve(false);
    solve(true);
}
