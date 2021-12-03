#!/bin/sh
# Copyright (c) 2021, Kis Imre. All rights reserved.
# SPDX-License-Identifier: MIT

DAY=$1

mkdir day${DAY}

cat << EOF > day${DAY}/day${DAY}.cpp
/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <fstream>
#include <iostream>

void part1() {
    std::fstream input("input");

    std::cout << 0 << std::endl;
}

void part2() {
    std::fstream input("input");

    std::cout << 0 << std::endl;
}

int main() {
    part1();
    part2();
}
EOF

cat << EOF > day${DAY}/day.mk
# Copyright (c) 2021, Kis Imre. All rights reserved.
# SPDX-License-Identifier: MIT

objs += day${DAY}.o
EOF

touch day${DAY}/input
