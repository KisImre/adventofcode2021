/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#ifndef AMPHIPOD_H_
#define AMPHIPOD_H_

#include <cstdint>
#include "Action.h"

struct Map;

struct Amphipod {
    enum Action get_possible_actions(const Map &map) const;
    void do_action(Map &map, Action action);

    bool is_in_place(const Map &map) const;

    mutable bool in_place = false;
    int target_room = -1;
    int8_t hallway_pos = -1;
    int8_t room_index = -1;
    int8_t room_depth = -1; // greater -> lower
};

#endif /* AMPHIPOD_H_ */