/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <fstream>
#include <iostream>
#include <string>

int64_t test_with_original_code(const std::string &data) {
    std::fstream input("input");
    std::string instr;
    std::string arg0, arg1;
    uint8_t data_index = 0;
    int64_t vars[4] = {0};

    while (input >> instr) {
        input >> arg0;
        int64_t& res = vars[arg0.front() - 'w'];

        if (instr.compare("inp") == 0) {
            res = data.c_str()[data_index++] - '0';
        } else if (instr.compare("add") == 0) {
            input >> arg1;
            int64_t val = ('w' <= arg1.front() && arg1.front() <= 'z') ? vars[arg1.front() - 'w'] : std::stol(arg1);
            res += val;
        } else if (instr.compare("mul") == 0) {
            input >> arg1;
            int64_t val = ('w' <= arg1.front() && arg1.front() <= 'z') ? vars[arg1.front() - 'w'] : std::stol(arg1);
            res *= val;
        } else if (instr.compare("div") == 0) {
            input >> arg1;
            int64_t val = ('w' <= arg1.front() && arg1.front() <= 'z') ? vars[arg1.front() - 'w'] : std::stol(arg1);
            res /= val;
        } else if (instr.compare("mod") == 0) {
            input >> arg1;
            int64_t val = ('w' <= arg1.front() && arg1.front() <= 'z') ? vars[arg1.front() - 'w'] : std::stol(arg1);
            res %= val;
        } else if (instr.compare("eql") == 0) {
            input >> arg1;
            int64_t val = ('w' <= arg1.front() && arg1.front() <= 'z') ? vars[arg1.front() - 'w'] : std::stol(arg1);
            res = ((int64_t)res == (int64_t)val) ? 1 : 0;
        }
    }

    return vars[3];
}

int64_t f(int64_t z, int64_t data, int64_t mod_add, int64_t res_add) {
    int64_t div = z / 26;
    int64_t mod = z % 26;

    int64_t res = 0;

    if ((mod + mod_add) != data) {
        res = div * 26 + data + res_add;
    } else {
        res = div;
    }

    return res;
}

int64_t shift_and_add_mod(int64_t z, int64_t data, int64_t res_add) {
    return z * 26 + data + res_add;
}

int64_t test_with_reversed_code(const std::string &data_str) {
    int64_t data[16];

    int i = 0;
    for (auto c : data_str) {
        data[i++] = c - '0';
    }

    int64_t z = data[0];
    z = shift_and_add_mod(z, data[1], 6);   //z = (data[0] * 26) + data[1] + 6
    z = shift_and_add_mod(z, data[2], 4);   // z = ((data[0] * 26) + data[1] + 6) + data[2] + 4
    z = shift_and_add_mod(z, data[3], 2);   // z = (((data[0] * 26) + data[1] + 6) + data[2] + 4) + data[3] + 2
    z = shift_and_add_mod(z, data[4], 9);   // z = ((((data[0] * 26) + data[1] + 6) + data[2] + 4) + data[3] + 2) + data[4] + 9
    z = f(z, data[5], -2, 1);               // z = (((data[0] * 26) + data[1] + 6) + data[2] + 4) + data[3] + 2, condition:  data[4] + 7 == data[5]
    z = shift_and_add_mod(z, data[6], 10);  // z = ((((data[0] * 26) + data[1] + 6) + data[2] + 4) + data[3] + 2) + data[6] + 10
    z = f(z, data[7], -15, 6);              // z = (((data[0] * 26) + data[1] + 6) + data[2] + 4) + data[3] + 2, condition: data[6] - 5 == data[7]
    z = f(z, data[8], -10, 4);              // z = ((data[0] * 26) + data[1] + 6) + data[2] + 4, condition: data[3] - 8 == data[8]
    z = shift_and_add_mod(z, data[9], 6);   // z = (((data[0] * 26) + data[1] + 6) + data[2] + 4) + data[9] + 6
    z = f(z, data[10], -10, 3);             // z = ((data[0] * 26) + data[1] + 6) + data[2] + 4, condition: data[9] - 4 == data[10] ok
    z = f(z, data[11], -4, 9);              // z = (data[0] * 26) + data[1] + 6, condition: data[2] == data[11] ok
    z = f(z, data[12], -1, 15);             // z = data[0] * 26, condition: data[1] + 5 == data[12] ok
    z = f(z, data[13], -1, 5);              // z = data[0], condition: data[0] - 1 == data[13] ok

    return z;
}

int main() {
    // Conditions
    // data[0] == data[13] + 1
    // data[1] == data[12] - 5
    // data[2] == data[11]
    // data[3] == data[8] + 8
    // data[4] == data[5] - 7
    // data[6] == data[7] + 5
    // data[9] == data[10] + 4

    std::cout << "test_with_original_code(\"94992994195998\") = " << test_with_original_code("94992994195998") << std::endl;
    std::cout << "test_with_reversed_code(\"94992994195998\") = " << test_with_reversed_code("94992994195998") << std::endl;

    std::cout << "test_with_original_code(\"21191861151161\") = " << test_with_original_code("21191861151161") << std::endl;
    std::cout << "test_with_reversed_code(\"21191861151161\") = " << test_with_reversed_code("21191861151161") << std::endl;
}
