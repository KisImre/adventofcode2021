/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#ifndef MATRIX_H
#define MATRIX_H

#include <cstring>
#include <iostream>
#include <list>
#include "Point.h"

static const int cos_lut[4] = {1, 0, -1, 0};
static const int sin_lut[4] = {0, 1, 0, -1};

struct Matrix {
    Matrix operator *(const Matrix &other) const {
        Matrix res;

        res.m[0][0] = m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0] + m[0][2] * other.m[2][0];
        res.m[0][1] = m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1] + m[0][2] * other.m[2][1];
        res.m[0][2] = m[0][0] * other.m[0][2] + m[0][1] * other.m[1][2] + m[0][2] * other.m[2][2];
        res.m[1][0] = m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0] + m[1][2] * other.m[2][0];
        res.m[1][1] = m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1] + m[1][2] * other.m[2][1];
        res.m[1][2] = m[1][0] * other.m[0][2] + m[1][1] * other.m[1][2] + m[1][2] * other.m[2][2];
        res.m[2][0] = m[2][0] * other.m[0][0] + m[2][1] * other.m[1][0] + m[2][2] * other.m[2][0];
        res.m[2][1] = m[2][0] * other.m[0][1] + m[2][1] * other.m[1][1] + m[2][2] * other.m[2][1];
        res.m[2][2] = m[2][0] * other.m[0][2] + m[2][1] * other.m[1][2] + m[2][2] * other.m[2][2];

        return res;
    }

    Point operator *(const Point &p) const {
        return { m[0][0] * p.x + m[0][1] * p.y + m[0][2] * p.z,
                 m[1][0] * p.x + m[1][1] * p.y + m[1][2] * p.z,
                 m[2][0] * p.x + m[2][1] * p.y + m[2][2] * p.z};
    }

    bool operator ==(const Matrix &other) const {
        return (memcmp(m, other.m, sizeof(m)) == 0);
    }

    bool operator <(const Matrix &other) const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (m[i][j] < other.m[i][j])
                    return true;
                else if (m[i][j] > other.m[i][j])
                    return false;
            }
        }

        return false;
    }

    static Matrix rotation_x(unsigned count) {
        return {{{1, 0, 0}, {0, cos_lut[count], -sin_lut[count]}, {0, sin_lut[count], cos_lut[count]}}};
    }

    static Matrix rotation_y(unsigned count) {
        return {{{cos_lut[count], 0, sin_lut[count]}, {0, 1, 0}, {-sin_lut[count], 0, cos_lut[count]}}};
    }

    static Matrix rotation_z(unsigned count) {
        return {{{cos_lut[count], -sin_lut[count], 0}, {sin_lut[count], cos_lut[count], 0}, {0, 0, 1}}};
    }

    static Matrix rotation(unsigned x, unsigned y, unsigned z) {
        return rotation_x(x) * rotation_y(y) * rotation_z(z);
    }

    static std::list<Matrix> generate_rotation_matrices() {
        std::list<Matrix> matrices;

        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                for (int z = 0; z < 4; z++) {
                    matrices.push_back(Matrix::rotation(x, y, z));
                }
            }
        }

        matrices.sort();
        matrices.unique();

        return matrices;
    }

    int m[3][3];
};

#endif /* MATRIX_H */