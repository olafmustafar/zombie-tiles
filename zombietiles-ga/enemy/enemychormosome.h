#pragma once

#include "genetic-algorithm/chromosome.hpp"
#include <models/enemy.hpp>
#include <vector>

struct EnemyChormosome : Chromosome {
public:
    EnemyChormosome();
    void randomize() override;
    void mutate() override;
    void crossover(Chromosome* other) override;
    string to_string() const override;

    std::vector<Enemy> enemies;
};
