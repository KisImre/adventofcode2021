/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include "Map.h"
#include "Amphipod.h"
#include <algorithm>
#include <cstring>
#include <iostream>

bool Map::is_room_enterance_empty(uint8_t room, uint8_t room_depth) const {
    for (int8_t i = room_depth - 1; i >= 0; i--) {
        if (rooms[room][i] != -1) {
            return false;
        }
    }
    return true;
}

bool Map::is_hallway_free(uint8_t from, uint8_t to) const {
    const uint8_t s = std::min(from, to);
    const uint8_t e = std::max(from, to);

    for (uint8_t i = s; i <= e; i++) {
        if (i != from && hallway[i] >= 0) {
            return false;
        }
    }

    return true;
}

bool Map::does_room_have_space(uint8_t room) const {
    for (uint8_t i = 0; i < room_depth; i++) {
        if (rooms[room][i] == -1) {
            return true;
        }
    }
    return false;
}

bool Map::is_room_bottom_ok(uint8_t room) const {
    for (uint8_t i = 0; i < room_depth; i++) {
        if (rooms[room][i] != room && rooms[room][i] != -1) {
            return false;
        }
    }
    return true;
}

uint8_t Map::get_target_room_depth(uint8_t room) const {
    for (uint8_t i = room_depth - 1; i >= 0; i--) {
        if (rooms[room][i] == -1) {
            return i;
        }
    }
    return -1;
}

bool Map::is_solved() const {
    return solved_count == amphipod_count;
}

void Map::print() const {
    char c[] = "#############\n#...........#\n###.#.#.#.###\n  #.#.#.#.#  \n  #.#.#.#.#  \n  #.#.#.#.#  \n  #########";

    for (size_t i = 0; i < amphipod_count; i++) {
        if (amphipods[i].hallway_pos >= 0) {
            c[amphipods[i].hallway_pos + 15] = amphipods[i].target_room + 'A';
        } else {
            c[amphipods[i].room_index * 2 + 31 + (amphipods[i].room_depth * 14)]  = amphipods[i].target_room + 'A';
        }
    }
    std::cout << c << std::endl;
}

Hash Map::hash() const {
    Hash hash = {0};
    for (size_t i = 0; i < 8; i++) {
        hash.a <<= 5;
        if (amphipods[i].hallway_pos >= 0) {
            static const uint32_t h[] = {16, 17, 0, 18, 0, 19, 0, 20, 0, 21, 22};
            hash.a |= h[amphipods[i].hallway_pos];
        } else {
            hash.a |= amphipods[i].room_index * room_depth + amphipods[i].room_depth;
        }
    }
    for (size_t i = 8; i < amphipod_count; i++) {
        hash.b <<= 5;
        if (amphipods[i].hallway_pos >= 0) {
            static const uint32_t h[] = {16, 17, 0, 18, 0, 19, 0, 20, 0, 21, 22};
            hash.b |= h[amphipods[i].hallway_pos];
        } else {
            hash.b |= amphipods[i].room_index * room_depth + amphipods[i].room_depth;
        }
    }
    return hash;
}

Map Map::create_from_string(const char *str) {
    Map map;
    int k = 0;
    map.amphipod_count = strlen(str);
    map.room_depth = map.amphipod_count / 4;
    map.solved_count = 0;
    for (int i = 0; i < 4; i++) {
        for (size_t j = 0; j < map.room_depth; j++) {
            map.amphipods[k].target_room = str[0] - 'A';
            map.amphipods[k].room_index = i;
            map.amphipods[k].room_depth = j;
            map.rooms[i][j] = map.amphipods[k].target_room;
            map.amphipods[k].hallway_pos = -1;
            ++k;
            ++str;
        }
    }
    for (int i = 0; i < 11; i++) {
        map.hallway[i] = -1;
    }

    uint8_t count = 0;
    for (size_t i = 0; i < map.amphipod_count; i++) {
        if (map.amphipods[i].is_in_place(map)) {
            map.amphipods[i].in_place = true;
            ++count;
        }
    }
    map.solved_count = count;

    return map;
}
