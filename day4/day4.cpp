/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>

class Bingo {
    public:
        explicit Bingo(std::istream &stream) {
            unsigned int n = 0;
            numbers.resize(size * size);
            for (size_t i = 0; i < size * size; i++) {
                stream >> n;
                numbers[i] = n;
            }
        }

        void select_number(unsigned int n) {
            auto match = std::find(numbers.begin(), numbers.end(), n);
            if (match != numbers.end()) {
                unsigned int index = std::distance(numbers.begin(), match);
                rows[index / size] |= 1 << (index % size);
                cols[index % size] |= 1 << (index / size);

                winner = winner || (rows[index / size] == winner_pattern)  || (cols[index % size] == winner_pattern);
            }
        }

        bool is_winner() {
            return winner;
        }

        unsigned int score(unsigned int n) {
            unsigned score = 0;
            for (size_t i = 0; i < numbers.size(); i++) {
                if ((rows[i / size] & (1 << (i % size))) == 0) {
                    score += numbers[i];
                }
            }

            return score * n;
        }

        static const size_t size = 5;
        static const uint8_t winner_pattern = (1 << size) - 1;

    private:
        std::vector<uint8_t> numbers;
        uint8_t rows[size] = { 0 };
        uint8_t cols[size] = { 0 };
        bool winner = false;
};

void part1() {
    std::fstream input("input");
    std::list<uint8_t> numbers;
    std::list<Bingo> bingos;
    unsigned int n = 0;
    char c = ',';

    while (c == ',') {
        input >> n >> c;
        numbers.push_back(n);
    }
    input.putback(c);

    while(!input.eof()) {
        bingos.push_back(Bingo(input));
    }

    for(auto n : numbers) {
        for (auto& b : bingos) {
            b.select_number(n);
            if (b.is_winner()) {
                std::cout << b.score(n) << std::endl;
                return;
            }
        }
    }

    std::cout << "No result" << std::endl;
}

void part2() {
    std::fstream input("input");

    std::cout << 0 << std::endl;
}

int main() {
    part1();
    part2();
}
