#include "enemychormosome.h"
#include "models/dungeonmatrix.hpp"
#include "models/point.hpp"

#include <iostream>
#include <models/dungeonconfig.hpp>
#include <models/enemiesconfig.hpp>
#include <sstream>
#include <unordered_set>
#include <utils/randomgenerator.hpp>
#include <utils/singleton.hpp>

namespace {
constexpr double GENE_MUTATION_RATE = 0.25;
constexpr double ATRIBUTE_MUTATION_RATE = 0.05;
}

EnemyChormosome::EnemyChormosome()
    : m_config { Singleton<EnemiesConfig>().get_instance() }
    , m_dungeon { *m_config.current_dungeon }
    , m_enemies_count { DungeonConfig::get_instance().get_rooms_count() * m_config.enemy_count_by_room }
    , m_min { m_config.min_att_value }
    , m_max { m_config.max_att_value }
    , m_genes { std::vector<EnemyGene> { m_enemies_count, EnemyGene {} } }
{
}

void EnemyChormosome::randomize()
{
    for (auto& g : m_genes) {
        g.room = Random::random_between(0, m_dungeon.rooms().size() - 1);
        g.damage = Random::random_between(m_min, m_max);
        g.health = Random::random_between(m_min, m_max);
        g.velocity = Random::random_between(m_min, m_max);
        g.attackCooldown = Random::random_between(m_min, m_max);
    }
}

void EnemyChormosome::mutate()
{
    size_t count = (m_enemies_count * GENE_MUTATION_RATE);
    size_t begin = Random::random_between(0, m_genes.size() - count - 1);
    size_t end = begin + count;

    for (size_t i = begin; i < end; i++) {
        auto& g = m_genes[i];
        if (Random::random_bool()) {
            g.room = Random::random_between(0, m_dungeon.rooms().size() - 1);
        } else {
            const int a = m_max * ATRIBUTE_MUTATION_RATE; // mutation amount
            g.damage = std::clamp(g.damage + Random::random_between(-a, +a), m_min, m_max);
            g.health = std::clamp(g.health + Random::random_between(-a, +a), m_min, m_max);
            g.velocity = std::clamp(g.velocity + Random::random_between(-a, +a), m_min, m_max);
            g.attackCooldown = std::clamp(g.attackCooldown + Random::random_between(-a, +a), m_min, m_max);
        }
    }
}

void EnemyChormosome::crossover(Chromosome* other)
{
    EnemyChormosome* o_enemy = static_cast<EnemyChormosome*>(other);

    for (size_t i = 0; i < m_genes.size(); i++) {
        if (i % 2 == 0) {
            swap(m_genes[i], o_enemy->m_genes[i]);
        }
    }
}

string EnemyChormosome::to_string() const
{
    std::stringstream ss;
    ss << "enemyChormosome(";
    for (const auto& g : m_genes) {
        ss << "room: " << g.room;
        ss << "health" << g.health;
        ss << "damage" << g.damage;
        ss << "attackCooldown" << g.attackCooldown;
        ss << "velocity" << g.velocity;
    }
    ss << ")";
    return ss.str();
}

std::vector<Enemy> EnemyChormosome::to_enemies(const DungeonMatrix& dm) const
{
    std::vector<Enemy> enemies = {};
    enemies.reserve(m_dungeon.rooms().size() * Singleton<EnemiesConfig>().get_instance().enemy_count_by_room);

    std::vector<std::vector<Point>> positions_per_room = { m_dungeon.rooms().size(), std::vector<Point> {} };

    for (size_t x = 0; x < dm.width(); x++) {
        for (size_t y = 0; y < dm.height(); y++) {
            Point pos = { x, y };
            if (dm[pos] == DungeonMatrix::EMPTY) {
                continue;
            }
            positions_per_room[dm[pos]].push_back(pos);
        }
    }

    std::unordered_set<Point> used_positions {};
    for (auto& gene : m_genes) {
        auto& available_positions = positions_per_room[gene.room];
        if (available_positions.empty()) {
            continue;
        }

        Point pos = {};
        do {
            if (available_positions.empty()) {
                break;
            }
            int e = Random::random_between(0, available_positions.size() - 1);
            pos = available_positions[e];
            available_positions.erase(available_positions.begin() + e);
        } while (used_positions.contains(pos));

        used_positions.insert(pos);

        enemies.push_back(Enemy { pos, gene.health, gene.damage, gene.attackCooldown, gene.velocity });
    }

    return enemies;
}

const std::vector<EnemyGene>& EnemyChormosome::genes() const
{
    return m_genes;
}
