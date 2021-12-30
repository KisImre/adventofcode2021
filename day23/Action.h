/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#ifndef ACTION_H_
#define ACTION_H_

enum Action {
    no_action = 0,
    move_to_room = 0x01,
    move_hallway0 = 0x02,
    move_hallway1 = 0x04,
    move_hallway3 = 0x08,
    move_hallway5 = 0x10,
    move_hallway7 = 0x20,
    move_hallway9 = 0x40,
    move_hallway10 = 0x80
};

#endif /* ACTION_H_ */
