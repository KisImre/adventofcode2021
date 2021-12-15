/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <cstring>
#include <fstream>
#include <iostream>

#define SIZE (500)

uint8_t map[SIZE][SIZE];
uint16_t distances[SIZE][SIZE];
bool visited[SIZE][SIZE];

void find_min(unsigned int *x, unsigned int *y) {
    uint16_t min = 0xffff;
    *x = 0;
    *y = 0;
    for (unsigned int a = 0; a < SIZE; a++) {
        for (unsigned int b = 0; b < SIZE; b++) {
            if (!visited[a][b] && distances[a][b] < min) {
                min = distances[a][b];
                *x = b;
                *y = a;
            }
        }
    }
    visited[*y][*x] = true;
}

void solve(bool scale_map) {
    std::fstream input("input");

    uint32_t row = 0, col = 0;
    for (std::string line; input >> line; ) {
        col = 0;
        for (auto c : line) {
            map[row][col] = c - '0';
            col++;
        }
        row++;
    }

    if(scale_map) {
        for (unsigned int i = 0; i < 5; i++) {
            for (unsigned int j = 0; j < 5; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }

                const unsigned int x_add = j * col;
                const unsigned int y_add = i * row;
                for (unsigned int y = 0; y < row; y ++) {
                    for (unsigned int x = 0; x < col; x++) {
                        map[y + y_add][x + x_add] = ((map[y][x] + i + j - 1) % 9) + 1;
                    }
                }
            }
        }
        row *= 5;
        col *= 5;
    }

    memset(distances, 0xff, sizeof(distances));
    memset(visited, 0x00, sizeof(visited));
    distances[0][0] = 0;

    uint32_t v_count = 1;
    const uint32_t max_count = row * col;
    uint32_t x = 0, y = 0;
    static const int offsets[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    while (v_count < max_count) {
        find_min(&x, &y);
        v_count++;

        uint32_t dist = map[y][x] + distances[y][x];
        for (int i = 0; i < 4; i++) {
            const uint32_t x_neighbour = x + offsets[i][0];
            const uint32_t y_neighbour = y + offsets[i][1];
            if (x_neighbour < col && y_neighbour < row && distances[y_neighbour][x_neighbour] > dist) {
                distances[y_neighbour][x_neighbour] = dist;
            }
        }
    }

    std::cout << distances[row - 1][col - 1] + map[row - 1][col - 1] - map[0][0] << std::endl;
}

int main() {
    solve(false);
    solve(true);
}
