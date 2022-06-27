#pragma once

#include "genetic-algorithm/chromosome.hpp"
#include "models/dungeonconfig.hpp"
#include "models/enemiesconfig.hpp"
#include "models/dungeon.hpp"
#include <vector>

struct EnemyGene {
    int32_t room;
    uint32_t health;
    uint32_t damage;
    uint32_t attackCooldown;
    uint32_t velocity;
};

struct EnemyChormosome : Chromosome {
public:
    EnemyChormosome();
    void randomize() override;
    void mutate() override;
    void crossover(Chromosome* other) override;
    std::vector<Enemy> to_enemies(const DungeonMatrix& dm) const;
    string to_string() const override;
    const std::vector<EnemyGene>& genes() const;


private:
    const EnemiesConfig& m_config;
    const Dungeon& m_dungeon;
    const size_t m_enemies_count;
    const uint32_t m_min;
    const uint32_t m_max;
    std::vector<EnemyGene> m_genes;

};
