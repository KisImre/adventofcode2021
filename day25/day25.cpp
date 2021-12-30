/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <fstream>
#include <iostream>
#include <cstring>

char map[200][200] = {0};

int main() {
    std::fstream input("input");
    uint32_t width = 0, height = 0;

    for (std::string line; input >> line; ) {
        width = 0;
        for (auto c : line) {
            map[height][width++] = c;
        }
        ++height;
    }

    bool moved = true;
    uint32_t iteration_count = 0;
    while (moved) {
        char map_temp[200][200] = {0};

        memset(map_temp, '.', sizeof(map));
        moved = false;

        // East
        for (uint32_t y = 0; y < height; y++) {
            bool first_empty = map[y][0] == '.';

            for (uint32_t x = 0; x < width; x++) {
                uint32_t next_x = (x + 1) % width;

                if (map[y][x] == '>' && ((next_x == 0 && first_empty) || map[y][next_x] == '.')) {
                    map_temp[y][x] = '.';
                    map_temp[y][next_x] = '>';
                    moved = true;
                } else if (map_temp[y][x] == '.')  {
                    map_temp[y][x] = map[y][x];
                }
            }
        }
        memcpy(map, map_temp, sizeof(map));

        // South
        for (uint32_t x = 0; x < width; x++) {
            bool first_empty = (map[0][x] == '.');
            for (uint32_t y = 0; y < height; y++) {
                uint32_t next_y = (y + 1) % height;

                if (map[y][x] == 'v' && ((next_y == 0 && first_empty) || map[next_y][x] == '.')) {
                    map_temp[y][x] = '.';
                    map_temp[next_y][x]= 'v';
                    moved = true;
                } else if (map_temp[y][x] == '.') {
                    map_temp[y][x] = map[y][x];
                }
            }
        }
        memcpy(map, map_temp, sizeof(map));

        iteration_count++;
    }

    std::cout << iteration_count << std::endl;
}
