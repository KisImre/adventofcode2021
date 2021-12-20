/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <cstdio>
#include <iostream>

int  main() {
    int target_x_start = 0, target_x_end = 0, target_y_start = 0, target_y_end = 0, max_peak = 0, count = 0;

    FILE *fp = fopen("input", "rt");
    fscanf(fp, "target area: x=%d..%d, z=%d..%d", &target_x_start, &target_x_end, &target_y_start, &target_y_end);
    fclose(fp);

    for (int vx = 0; vx < 1000; vx++) {
        for (int vy = -1000; vy <= 1000; vy++) {
            int x = 0, y = 0, vx_temp = vx, vy_temp = vy, peak = 0;
            bool matched = false;

            while (x <= target_x_end && y >= target_y_start) {
                if (target_x_start <= x && x <= target_x_end && target_y_start <= y && y <= target_y_end && !matched) {
                    max_peak = std::max(max_peak, peak);
                    ++count;
                    matched = true;
                }

                x += vx_temp;
                y += vy_temp;
                vx_temp = vx_temp ? vx_temp - 1 : 0;
                vy_temp -= 1;
                peak = std::max(peak, y);
            }
        }
    }

    std::cout << max_peak << std::endl;
    std::cout << count << std::endl;
}
