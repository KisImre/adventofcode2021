/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <fstream>
#include <iostream>
#include <map>
#include "Amphipod.h"
#include "Map.h"

std::map<Hash, uint32_t> cache;

uint32_t solve(Map& map, uint32_t current_min_cost) {
    uint32_t cost = 0xffffffff;

    if (current_min_cost < map.cost) {
        // Early fail
        return 0xffffffff;
    }

    if (map.is_solved()) {
        return map.cost;
    }

    Hash hash = map.hash();
    if (cache.find(hash) != cache.end()) {
        if (cache[hash] == 0xffffffff) {
            return 0xffffffff;
        }
        return cache[hash] + map.cost;
    }

    for (size_t i = 0; i < map.amphipod_count; i++) {
        if (!map.amphipods[i].is_in_place(map)) {
            uint8_t actions = map.amphipods[i].get_possible_actions(map);
            if (actions) {
                for (uint8_t j = 1; j != 0; j<<=1) {
                    if (actions & j) {
                        Map map_temp = map;
                        map_temp.amphipods[i].do_action(map_temp, (Action)j);
                        cost = std::min(solve(map_temp, cost), cost);
                    }
                }
            }
        }
    }

    if (cost != 0xffffffff) {
        cache[hash] = (cost - map.cost);
    } else {
        cache[hash] = 0xffffffff;
    }

    return cost;
}

int main() {
    Map map1 = Map::create_from_string("DCAADBCB");
    std::cout << solve(map1, 0xffffffff) << std::endl;

    Map map2 = Map::create_from_string("DDDCACBADBABCACB");
    std::cout << solve(map2, 0xffffffff) << std::endl;
}
