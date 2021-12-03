/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <fstream>
#include <iostream>
#include <string>

void part1() {
    std::string command;
    int parameter = 0;
    int horizonal_position = 0;
    int depth = 0;

    std::fstream input("input");

    while(!input.eof()) {
        input >> command >> parameter;
        switch(command.c_str()[0]) {
            case 'f':
                horizonal_position += parameter;
                break;
            case 'u':
                depth -= parameter;
                break;
            case 'd':
                depth += parameter;
                break;

        }
    }

    std::cout << horizonal_position * depth << std::endl;
}

void part2() {
    std::string command;
    int parameter = 0;
    int horizonal_position = 0;
    int depth = 0;
    int aim = 0;

    std::fstream input("input");

    while(!input.eof()) {
        input >> command >> parameter;
        switch(command.c_str()[0]) {
            case 'f':
                horizonal_position += parameter;
                depth += parameter * aim;
                break;
            case 'u':
                aim -= parameter;
                break;
            case 'd':
                aim += parameter;
                break;

        }
    }

    std::cout << horizonal_position * depth << std::endl;
}

int main() {
    part1();
    part2();
}