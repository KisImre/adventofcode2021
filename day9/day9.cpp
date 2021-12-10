/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <map>

typedef std::map<uint8_t, uint8_t> row_type;
typedef std::map<uint8_t, row_type> map_type;

template<typename T>
T get_cell(map_type &map, int x, int y, T default_value) {
    if (y < 0 || (int)map.size() <= y || x < 0 || (int)map[0].size() <= x)
        return default_value;
    return map[y][x];
}

int main() {
    std::fstream input("input");
    std::string row;
    map_type map, basin_map;
    unsigned int rows = 0;

    while (input >> row) {
        map[rows] = std::map<uint8_t, uint8_t>();
        for(size_t i = 0; i < row.size(); i++) {
            map[rows][i] = row[i] - '0';
        }
        ++rows;
    }

    std::map<unsigned int, unsigned int> basin_sizes;
    unsigned int basin_index = 1;
    unsigned int uncovered = rows * map[0].size();
    unsigned int sum = 0;
    static const int offsets[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (size_t y = 0; y < map.size(); y++) {
        for (size_t x = 0; x < map[y].size(); x++) {
            uint8_t current_height = map[y][x];
            bool res = true;

            for (int d = 0; d < 4; d++) {
                res = res && (get_cell<uint8_t>(map, x + offsets[d][0], y + offsets[d][1], 10) > current_height);
            }

            if (res) {
                basin_sizes[basin_index] = 1;
                basin_map[y][x] = basin_index++;
                --uncovered;
                sum += current_height + 1;
            }
        }
    }

    for (unsigned int y = 0; y < map.size(); y++) {
        for (unsigned int x = 0; x < map[y].size(); x++) {
            if (map[y][x] == 9) {
                basin_map[y][x] = 0xff;
                --uncovered;
            }
        }
    }

    while(uncovered) {
        for (unsigned int y = 0; y < map.size(); y++) {
            for (unsigned int x = 0; x < map[y].size(); x++) {
                if (basin_map[y][x] == 0 || basin_map[y][x] == 0xff)
                    continue;

                unsigned int new_cover_count = 0;
                uint8_t current_basin = basin_map[y][x];

                // Already covered
                for (int d = 0; d < 4; d++) {
                    if (get_cell<unsigned int>(basin_map, x + offsets[d][0], y + offsets[d][1], 0xff) == 0){
                        basin_map[y + offsets[d][1]][x + offsets[d][0]] = current_basin;
                        ++new_cover_count;
                    }
                }

                uncovered -= new_cover_count;
                basin_sizes[current_basin] += new_cover_count;
            }
        }
    }

    std::list<int> size_list;
    for (auto &basin_size : basin_sizes) {
        size_list.push_back(basin_size.second);
    }

    size_list.sort();
    size_list.reverse();

    auto it = size_list.begin();
    unsigned int basin_sum = 1;
    for (int x = 0; x < 3; x++) {
        basin_sum *= *it++;
    }

    std::cout << sum << std::endl;
    std::cout << basin_sum << std::endl;
}
