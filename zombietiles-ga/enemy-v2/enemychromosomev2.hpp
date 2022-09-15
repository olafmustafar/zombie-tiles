#pragma once

#include "genetic-algorithm/chromosome.hpp"
#include "zombietiles-ga/dungeon/roomgene.hpp"
#include <models/enemiesconfig.hpp>
#include <models/enemy.hpp>

namespace V2 {

struct EnemyChromosome : ChromosomeImpl<EnemyChromosome> {
public:
    EnemyChromosome();
    void randomize() override;
    void mutate() override;
    void crossover(EnemyChromosome* other) override;
    string to_string() const override;
    const std::vector<int>& genes() const;

private:
    const EnemiesConfig& ec;
    const size_t dungeon_size;
    std::vector<int> m_genes;
};

}
