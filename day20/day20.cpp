/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <cstring>
#include <fstream>
#include <iostream>

const struct {
    int x, y;
} offsets[9] = {
    {-1, -1}, {0, -1}, {1, -1},
    {-1, 0}, {0, 0}, {1, 0},
    {-1, 1}, {0, 1}, {1, 1},
};

struct Image {
    bool get_pixel(int x, int y, bool def_value) const {
        if (x < 0 || y < 0 || x >= width || y >= height) {
            return def_value;
        }
        return pixels[y][x];
    }

    Image enhance(std::string algorithm, bool def_value) {
        Image enhanced = {.width = width + 2, .height = height + 2};

        for (int y = -1; y < height + 1; y++) {
            for (int x = -1; x < width + 1; x++) {
                uint16_t algorithm_index = 0;
                for (int n = 0; n < 9; n++) {
                    algorithm_index = (algorithm_index << 1) | get_pixel(x + offsets[n].x, y + offsets[n].y, def_value);
                }
                enhanced.pixels[y + 1][x + 1] = (algorithm[algorithm_index] == '#');
            }
        }

        return enhanced;
    }

    unsigned int count_on_pixels() const {
        unsigned int count = 0;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                count += (unsigned int )(pixels[y][x]);
            }
        }
        return count;
    }

    bool pixels[1000][1000] = { 0 };
    int width = 0, height = 0;
};

std::istream &operator >>(std::istream &input, Image &image) {
    int x = 0, y = 0;
    for (std::string line; input >> line; y++) {
        x = 0;
        for (auto c : line) {
            image.pixels[y][x++] = (c == '#');
        }
    }
    image.width = x;
    image.height = y;

    return input;
}

void solve(unsigned int cycles) {
    std::fstream input("input");
    std::string algorithm;
    Image image;

    input >> algorithm >> image;

    bool def_value = false;
    for (unsigned int cycle = 0; cycle < cycles; cycle++) {
        image = image.enhance(algorithm, def_value);
        def_value = (def_value ? algorithm.back() : algorithm.front()) == '#';
    }

    std::cout << image.count_on_pixels() << std::endl;
}

int main() {
    solve(2);
    solve(50);
}
