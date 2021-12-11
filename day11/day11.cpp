/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <string>

template<typename T>
class Map2D {
    public:
        void add_value(unsigned int x, unsigned y, T value) {
            map[x][y] = value;
        }

        void for_each(const std::function<void(unsigned int x, unsigned int y, T &v)>& f) {
            for (auto col = map.begin(); col != map.end(); col++) {
                for (auto cell = col->second.begin(); cell != col->second.end(); cell++) {
                    f(std::distance(map.begin(), col), std::distance(col->second.begin(), cell), cell->second);
                }
            }
        }

        void apply_neighbors(unsigned int x, unsigned int y, const std::function<void(T &v)>& f) {
            for (int i = 0; i < 8; i++) {
                if (x + offsets[i][0] < map.size() && y + offsets[i][1] < map[x + offsets[i][0]].size()) {
                    f(map[x + offsets[i][0]][y + offsets[i][1]]);
                }
            }
        }

        size_t size() {
            return (map.size() > 0) ? map.size() * map[0].size() : 0;
        }

    private:
        std::map<unsigned int, std::map<unsigned int, T>> map;
        const int offsets[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
};

int main() {
    std::fstream input("input");
    std::string line;
    Map2D<uint8_t> map;

    for (unsigned int y = 0, x = 0; input >> line; y++, x = 0) {
        for (auto c : line) {
            map.add_value(x++, y, c - '0');
        }
    }

    unsigned int flashes_to_100 = 0, flashes_in_step = 0, flashes_in_substep = 0, step = 0;
    for (step = 0; flashes_in_step < map.size(); step++) {
        map.for_each([&](unsigned int x, unsigned int y, uint8_t& v){++v;});

        flashes_in_step = 0;
        do {
            flashes_in_substep = 0;
            map.for_each([&](unsigned int x, unsigned int y, uint8_t& v){
                if(v > 9) {
                    ++flashes_in_substep;
                    v = 0;
                    map.apply_neighbors(x, y, [&](uint8_t &neighbour){ if (neighbour > 0) ++neighbour; });
                }
            });

            flashes_in_step += flashes_in_substep;
        } while (flashes_in_substep);

        if (step < 100)
            flashes_to_100 += flashes_in_step;
    }

    std::cout << flashes_to_100 << std::endl;
    std::cout << step << std::endl;
}
