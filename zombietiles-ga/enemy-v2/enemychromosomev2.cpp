
#include "zombietiles-ga/enemy-v2/enemychromosomev2.hpp"
#include <cassert>
#include <models/enemiesconfig.hpp>
#include <models/enemy.hpp>
#include <models/enemypool.hpp>
#include <utils/randomgenerator.hpp>
#include <utils/singleton.hpp>

namespace {
constexpr float ADD_ENEMY_CHANCE = 0.3;
constexpr float MUTATION_CHANCE = 0.05;
constexpr float CROSSOVER_CHANCE = 0.30;
}

V2::EnemyChromosome::EnemyChromosome()
    : ec { St<EnemiesConfig> }
    , dungeon_size { ec.current_dungeon->rooms().size() }
    , m_genes(St<EnemyPool>.size(), -1)
{
}

void V2::EnemyChromosome::randomize()
{
    for (int& gene : m_genes) {
        if (Random::random_bool(ADD_ENEMY_CHANCE)) {
            gene = Random::random_between(0, dungeon_size - 1);
        }
    }
}

void V2::EnemyChromosome::mutate()
{
    for (int& gene : m_genes) {
        if (Random::random_bool(MUTATION_CHANCE)) {
            gene = Random::random_between<int>(-1, dungeon_size - 1);
        }
    }
}

void V2::EnemyChromosome::crossover(EnemyChromosome* other)
{
    for (size_t i = 0; i < m_genes.size(); i++) {
        if (Random::random_bool(CROSSOVER_CHANCE)) {
            swap(m_genes[i], other->m_genes[i]);
        }
    }
}

string V2::EnemyChromosome::to_string() const
{
    return "TODO to_string()";
}

const std::vector<int>& V2::EnemyChromosome::genes() const
{
    return m_genes;
}
