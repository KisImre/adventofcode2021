/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#ifndef POINT_H
#define POINT_H

#include <iostream>

struct Point {
    bool operator ==(const Point& other) const {
        return (x == other.x) && (y == other.y) && (z == other.z);
    }

    bool operator <(const Point& other) const {
        if (x < other.x) return true;
        if (x > other.x) return false;
        if (y < other.y) return true;
        if (y > other.y) return false;
        return z < other.z;
    }

    Point operator +(const Point& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    Point operator -(const Point& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    unsigned int manhattan_dist(const Point& other) const {
        return std::abs(x - other.x) + std::abs(y - other.y) + std::abs(z - other.z);
    }

    bool is_zero() const {
        return x == 0 && y == 0 && z == 0;
    }

    void print() const {
        std::cout << "(" << x << ", " << y << ", " << z << ")";
    }

    int x, y, z;
};

std::istream &operator >>(std::istream &input, Point &point) {
    char dummy = '\0';
    input >> point.x >> dummy >> point.y >> dummy >> point.z;
    return input;
}

#endif /* POINT_H */
