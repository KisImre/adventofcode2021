/* Copyright (c) 2021, Kis Imre. All rights reserved. */
/* SPDX-License-Identifier: MIT */

#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>

struct Player {
    uint32_t step(uint32_t dice) {
        position = ((position + dice - 1) % 10) + 1;
        score += position;
        return score;
    }

    uint32_t position = 0;
    uint32_t score = 0;
};

std::istream &operator >>(std::istream &input, Player &player) {
    input.seekg(28, std::ios_base::cur);
    input >> player.position;
    return input;
}

struct DeterministicDice {
    uint32_t next() {
        count++;
        return state = (state == 100) ? 1 : state + 1;
    }

    uint32_t state = 0;
    uint32_t count = 0;
};

struct PlayerResults {
    PlayerResults& operator +=(const PlayerResults &other) {
        player1wins += other.player1wins;
        player2wins += other.player2wins;
        return *this;
    }

    uint64_t player1wins = 0;
    uint64_t player2wins = 0;
};

void part1() {
    std::fstream input("input");
    DeterministicDice dice;
    Player player1, player2;

    input >> player1 >> player2;

    while (player1.step(dice.next() + dice.next() + dice.next()) < 1000 &&
        player2.step(dice.next() + dice.next() + dice.next()) < 1000);

    std::cout << std::min(player1.score, player2.score) * dice.count << std::endl;
}

std::map<uint64_t, PlayerResults> cache;

PlayerResults fork_worlds(Player player1, Player player2) {
    static const uint8_t dice_numbers[] = {3, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 8, 8, 8, 9};

    uint64_t call_id = ((player1.position * 10 + player2.position) * 21 + player1.score) * 21 + player2.score;
    auto cached_result = cache.find(call_id);
    if (cached_result != cache.end()) {
        return cached_result->second;
    }

    PlayerResults res = {0, 0};
    for (size_t i = 0; i < sizeof(dice_numbers); i++) {
        for (size_t j = 0; j < sizeof(dice_numbers); j++) {
            Player player1_temp = player1;
            if (player1_temp.step(dice_numbers[i]) >= 21) {
                ++res.player1wins;
                break;
            }

            Player player2_temp = player2;
            if (player2_temp.step(dice_numbers[j]) >= 21) {
                ++res.player2wins;
                continue;
            }

            res += fork_worlds(player1_temp, player2_temp);
        }
    }

    cache[call_id] = res;
    return res;
}

void part2() {
    std::fstream input("input");
    Player player1, player2;

    input >> player1 >> player2;

    PlayerResults r = fork_worlds(player1, player2);
    std::cout << std::max(r.player1wins, r.player2wins) << std::endl;
}

int main() {
    part1();
    part2();
}
