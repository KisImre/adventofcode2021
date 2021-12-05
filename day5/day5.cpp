/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>

struct Point {
    Point() = default;
    Point(int x, int y) : x(x), y(y) {}

    bool operator !=(const Point &other) const {
        return x != other.x || y != other.y;
    }

    Point &operator +=(const Point &other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    int x, y;
};

struct PointComparator {
    bool operator()(const Point& lhs, const Point& rhs) const {
        return (lhs.x != rhs.x) ? lhs.x < rhs.x : lhs.y < rhs.y;
    }
};

typedef std::map<Point, unsigned int, PointComparator> vent_map;

class Line {
    public:
        explicit Line(std::istream &input) {
            char c = '\0';
            input >> p1.x >> c >> p1.y;
            input.ignore(4);
            input >> p2.x >> c >> p2.y;
        }

        bool is_horizonal_or_vertical() const { return (p1.x == p2.x) || (p1.y == p2.y); }

        void mark_map(vent_map &map) {
            auto get_increment = [](auto a, auto b){ return (a < b) ? 1 : (a == b) ? 0 : -1; };
            Point p_diff(get_increment(p1.x, p2.x), get_increment(p1.y, p2.y));
            for(Point p = p1; map[p]++, p != p2; p += p_diff);
        }

    private:
        Point p1, p2;
};

int main() {
    std::fstream input("input");
    vent_map map;
    vent_map map_diagonal_too;

    while(!input.eof()) {
        Line l(input);
        if (l.is_horizonal_or_vertical()) {
            l.mark_map(map);
        }
        l.mark_map(map_diagonal_too);
    }

    std::cout << std::count_if(map.begin(), map.end(), [&](auto a) { return a.second >= 2; }) << std::endl;
    std::cout << std::count_if(map_diagonal_too.begin(), map_diagonal_too.end(), [&](auto a) { return a.second >= 2; }) << std::endl;
}
