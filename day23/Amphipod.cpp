/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include "Amphipod.h"
#include "Map.h"
#include <cstdlib>
#include <numeric>

static const int8_t hallway_above_rooms[4] = {2, 4, 6, 8};
static const uint8_t hw_positons[] = {0, 1, 3, 5, 7, 9, 10};
static const Action pos_to_action[] = {move_hallway0, move_hallway1, move_hallway3, move_hallway5, move_hallway7, move_hallway9, move_hallway10};

enum Action Amphipod::get_possible_actions(const Map& map) const {
    // Already in place
    if (is_in_place(map)) {
        return no_action;
    }

    Action actions = no_action;
    if (room_index >= 0) {
        // In room, but not in place
        if (!map.is_room_enterance_empty(room_index, room_depth)) {
            // Room enterance blocked
            return no_action;
        }

        for (uint8_t i = 0; i < sizeof(hw_positons); i++) {
            if(map.is_hallway_free(hallway_above_rooms[room_index], hw_positons[i])) {
                actions = (Action)(actions | pos_to_action[i]);
            }
        }

        // Move directly to room
        if (map.does_room_have_space(target_room) && map.is_hallway_free(hallway_above_rooms[room_index], hallway_above_rooms[target_room])) {
            actions = (Action)(actions | move_to_room);
        }
        return actions;
    } else if (map.does_room_have_space(target_room)) {
        // In hallway and there's room in the room
        if (map.is_hallway_free(hallway_pos, hallway_above_rooms[target_room])) {
            actions = (Action)(actions | move_to_room);
        }
    }

    return actions;
}

void Amphipod::do_action(Map &map, Action action) {
    uint8_t distance = 0;
    uint8_t depth = 0;
    int8_t hallway_pos_temp = 0;

    static const int8_t hallway_pos_lut[] = {0, 1, 3, 5, 7, 9, 10};
    static const uint32_t distance_costs[] = {1, 10, 100, 1000};

    switch (action)
    {
    case no_action:
        return;
    case move_to_room:
        if (hallway_pos < 0) {
            // Starting from room
            map.rooms[room_index][room_depth] = -1;
            distance += 1 + room_depth;
            distance += std::abs(hallway_above_rooms[room_index] - hallway_above_rooms[target_room]);
        } else {
            // Starting from hallway
            map.hallway[hallway_pos] = -1;
            distance += std::abs(hallway_pos - hallway_above_rooms[target_room]);
        }
        depth = map.get_target_room_depth(target_room);
        distance += depth + 1;

        hallway_pos = -1;
        room_index = target_room;
        room_depth = depth;
        map.rooms[room_index][room_depth] = target_room;

        in_place = true;
        map.solved_count++;
        break;
    case move_hallway0:
    case move_hallway1:
    case move_hallway3:
    case move_hallway5:
    case move_hallway7:
    case move_hallway9:
    case move_hallway10:
        distance += 1 + room_depth;
        hallway_pos_temp = hallway_pos_lut[(std::countr_zero((uint8_t)action) - std::countr_zero((uint8_t)move_hallway0))];
        distance += std::abs(hallway_above_rooms[room_index] - hallway_pos_temp);
        map.rooms[room_index][room_depth] = -1;
        room_index = room_depth = -1;
        hallway_pos = hallway_pos_temp;
        map.hallway[hallway_pos] = target_room;
        break;
    default:
        break;
    }

    map.cost += distance * distance_costs[target_room];
}

bool Amphipod::is_in_place(const Map &map) const {
    if (in_place) {
        return true;
    } else {
        return (room_index == target_room) && (room_depth == 1 || map.is_room_bottom_ok(target_room));
    }
}
