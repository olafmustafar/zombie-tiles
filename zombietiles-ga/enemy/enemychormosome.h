#pragma once

#include "genetic-algorithm/chromosome.hpp"
#include <models/enemy.hpp>
#include <models/roommap.hpp>
#include <vector>

struct EnemyChormosome : Chromosome {
public:
    EnemyChormosome();
    void randomize() override;
    void mutate() override;
    void crossover(Chromosome* other) override;
    string to_string() const override;

    const RoomMap& dungeon;
    std::vector<Enemy> enemies;
    const uint32_t min;
    const uint32_t max;
};
