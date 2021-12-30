/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <fstream>
#include <iostream>
#include <list>

struct Cube {
    bool has_limited_size() {
        return std::abs(x0) <= 50 && std::abs(x1) <= 50 &&
            std::abs(y0) <= 50 && std::abs(y1) <= 50 &&
            std::abs(z0) <= 50 && std::abs(z1) <= 50;
    }

    uint64_t volume() {
        return (x1 - x0 + 1) * (y1 - y0 + 1) * (z1 - z0 + 1);
    }

    bool operator <(const Cube& other) const {
        if (x0 < other.x0) return true;
        if (x0 > other.x0) return false;
        if (x1 < other.x1) return true;
        if (x1 > other.x1) return false;
        if (y0 < other.y0) return true;
        if (y0 > other.y0) return false;
        if (y1 < other.y1) return true;
        if (y1 > other.y1) return false;
        if (z0 < other.z0) return true;
        if (z0 > other.z0) return false;
        if (z1 < other.z1) return true;
        if (z1 > other.z1) return false;
        return false;
    }

    bool has_intersection(const Cube &other) const {
        return (std::max(x0, other.x0) <= std::min(x1, other.x1) &&
            std::max(y0, other.y0) <= std::min(y1, other.y1) &&
            std::max(z0, other.z0) <= std::min(z1, other.z1));
    }

    std::list<Cube> operator -(const Cube &other) const {
        std::list<Cube> slices;

        if (x0 < other.x0) // Bottom
            slices.push_back({ .on = on,
                .x0 = x0, .x1 = other.x0 - 1,
                .y0 = y0, .y1 = y1,
                .z0 = z0,.z1 = z1
            });

        if (other.x1 < x1) // Top
            slices.push_back({ .on = on,
                .x0 = other.x1 + 1, .x1 = x1,
                .y0 = y0, .y1 = y1, .z0 = z0, .z1 = z1
            });

        if (y0 < other.y0) // Left
            slices.push_back({ .on = on,
                .x0 = std::max(x0, other.x0), .x1 = std::min(x1, other.x1),
                .y0 = y0, .y1 = other.y0 - 1,
                .z0 = z0, .z1 = z1
            });

        if (other.y1 < y1) // Right
            slices.push_back({ .on = on,
                .x0 = std::max(x0, other.x0), .x1 = std::min(x1, other.x1),
                .y0 = other.y1 + 1, .y1 = y1,
                .z0 = z0, .z1 = z1
            });

        if (z0 < other.z0) // Back
            slices.push_back({ .on = on,
                .x0 = std::max(x0, other.x0), .x1 = std::min(x1, other.x1),
                .y0 = std::max(y0, other.y0), .y1 = std::min(y1, other.y1),
                .z0 = z0, .z1 = other.z0 - 1
            });

        if (other.z1 < z1) // Front
            slices.push_back({ .on = on,
                .x0 = std::max(x0, other.x0), .x1 = std::min(x1, other.x1),
                .y0 = std::max(y0, other.y0), .y1 = std::min(y1, other.y1),
                .z0 = other.z1 + 1, .z1 = z1
            });

        return slices;
    }

    bool on = false;
    int64_t x0 = 0, x1 = 0, y0 = 0, y1 = 0, z0 = 0, z1 = 0;
};

std::istream &operator >>(std::istream &input, Cube &cube) {
    std::string on_off, line;

    input >> on_off >> line;
    cube.on = (on_off.compare("on") == 0);
    sscanf(line.c_str(), "x=%ld..%ld,y=%ld..%ld,z=%ld..%ld",
        &cube.x0, &cube.x1, &cube.y0, &cube.y1, &cube.z0, &cube.z1);

    return input;
}

std::ostream &operator <<(std::ostream &output, const Cube &cube) {
    output << "x=" << cube.x0 << ".." << cube.x1 << "," <<
        "y=" << cube.y0 << ".." << cube.y1 << ","<<
        "z=" << cube.z0 << ".." << cube.z1;
    return output;
}

void solve(bool only_limited_size) {
    std::fstream input("input");
    std::list<Cube> unprocessed_cubes;
    std::list<Cube> cubes_turned_on;

    for(Cube cube; input >> cube; unprocessed_cubes.push_back(cube));

    for(auto& cube_to_process : unprocessed_cubes) {
        if (only_limited_size && !cube_to_process.has_limited_size()) {
            continue;
        }

        std::list<Cube> turned_on_slices_to_add;
        for (auto cube_turned_on = cubes_turned_on.begin(); cube_turned_on != cubes_turned_on.end(); ) {
            if (cube_to_process.has_intersection(*cube_turned_on)) {
                auto cube_turned_on_slices = *cube_turned_on - cube_to_process;
                turned_on_slices_to_add.merge(cube_turned_on_slices);
                cube_turned_on = cubes_turned_on.erase(cube_turned_on);
            } else {
                cube_turned_on++;
            }
        }

        cubes_turned_on.merge(turned_on_slices_to_add);

        if (cube_to_process.on) {
            cubes_turned_on.push_back(cube_to_process);
        }
    }

    uint64_t count = 0;
    for (auto &cubes_turned_on : cubes_turned_on) {
        count += cubes_turned_on.volume();
    }

    std::cout << count << std::endl;
}

int main() {
    solve(true);
    solve(false);
}
