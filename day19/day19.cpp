/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <algorithm>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>

#include "Point.h"
#include "Matrix.h"

struct Scanner {
    Scanner() = default;

    Scanner rotate(Matrix &rotation_matrix) {
        Scanner res = *this;
        for (auto &p : res.points) {
            p = rotation_matrix * p;
        }
        res.points.sort();
        return res;
    }

    Scanner move(Point &vector) {
        Scanner res = *this;
        for (auto &p : res.points) {
            p = p + vector;
        }
        return res;
    }

    void merge(Scanner &other) {
        points.merge(other.points);
        points.unique();
    }

    unsigned count_matching_points(Scanner &other) const {
        unsigned int res = 0;
        for (auto &p1 : points) {
            for (auto &p2 : other.points) {
                res += (p1 == p2);
            }
        }
        return res;
    }

    unsigned int id;
    std::list<Point> points;
};

std::istream &operator >>(std::istream &input, Scanner &scanner) {
    std::string dummy;

    scanner.points.clear();
    input >> dummy >> dummy >> scanner.id >> dummy;
    if (!input.good()) {
        return input;
    }

    for (Point p; input >> p; ) {
        scanner.points.push_back(p);
    }
    scanner.points.sort();
    input.clear();

    return input;
}


auto rotation_matrices = Matrix::generate_rotation_matrices();

Scanner find_match(std::list<Scanner> &scanners, Scanner &base_scanner, Point &offset_res) {
    for (auto& scanner : scanners) {
        if (base_scanner.id == scanner.id) {
            continue;
        }

        std::cout << "Comparing: " << base_scanner.id << " <-> " << scanner.id << std::endl;

        for (auto &rotation_matrix : rotation_matrices) {
            Scanner rotated = scanner.rotate(rotation_matrix);

            for (auto &base_point : base_scanner.points) {
                for (auto &p2 : rotated.points) {
                    Point offset = base_point - p2;
                    if (offset.is_zero())
                        continue;

                    Scanner moved = rotated.move(offset);

                    unsigned int c = base_scanner.count_matching_points(moved);
                    if (c >= 12) {
                        std::cout << "Match " << c << ", ";
                        offset.print();
                        std::cout << std::endl;
                        offset_res = offset;
                        return moved;
                    }
                }
            }
        }
    }

    return base_scanner; // Dummy
}

int main() {
    std::fstream input("input");
    std::list<Scanner> scanners;

    for (Scanner scanner; input >> scanner; ) {
        scanners.push_back(scanner);
    }

    Scanner res_scanner = scanners.front();
    scanners.pop_front();

    std::list<Point> offsets;

    while (scanners.size() > 0) {
        std::cout << "Remaining scanners: " << scanners.size() << std::endl;
        Point offset_res;
        auto match = find_match(scanners, res_scanner, offset_res);
        offsets.push_back(offset_res);
        res_scanner.merge(match);
        scanners.remove_if([&](auto& m){return m.id == match.id;});
    }

    unsigned int max_dist = 0;
    for (auto &o1 : offsets) {
        for (auto &o2 : offsets) {
            max_dist = std::max(max_dist, o1.manhattan_dist(o2));
        }
    }

    std::cout << res_scanner.points.size() << std::endl;
    std::cout << max_dist << std::endl;
}
