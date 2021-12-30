/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#ifndef MAP_H_
#define MAP_H_

#include <cstddef>
#include <cstdint>
#include "Action.h"
#include "Amphipod.h"

struct Hash {
    bool operator <(const Hash &other) const {
        if (a < other.a) return true;
        if (a > other.a) return false;
        return b < other.b;
    }

    uint64_t a;
    uint64_t b;
};

struct Map {
    bool is_room_enterance_empty(uint8_t room, uint8_t room_depth) const;
    bool is_hallway_free(uint8_t from, uint8_t to) const;
    bool does_room_have_space(uint8_t room) const;
    bool is_room_bottom_ok(uint8_t room) const;
    uint8_t get_target_room_depth(uint8_t room) const;

    bool is_solved() const;

    void print() const;

    Hash hash() const;

    static Map create_from_string(const char *str);

    Amphipod amphipods[16];
    size_t amphipod_count = 16;
    mutable uint8_t solved_count = 0;
    int8_t hallway[11] = {0};
    int8_t rooms[4][4] = {0};
    size_t room_depth = 4;
    uint32_t cost = 0;
};

#endif /* MAP_H_ */