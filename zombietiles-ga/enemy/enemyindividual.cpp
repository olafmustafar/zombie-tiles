#include "enemyindividual.h"
#include "helpers/roommaphelper.hpp"
#include "models/dungeonmatrix.hpp"
#include "models/enemiesmetadata.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <models/enemiesconfig.hpp>
#include <utils/singleton.hpp>

EnemyIndividual::EnemyIndividual()
    : enemies_config(Singleton<EnemiesConfig>::get_instance())
    , min_att { enemies_config.min_att_value }
    , max_att { enemies_config.max_att_value }
{
}

void EnemyIndividual::crossover(IndividualImpl* other)
{
    get_chromosome()->crossover(static_cast<EnemyIndividual*>(other)->get_chromosome());
}

void EnemyIndividual::mutate()
{
    get_chromosome()->mutate();
}

string EnemyIndividual::to_string() const
{
    return get_chromosome()->to_string();
}

double EnemyIndividual::calculate_fitness()
{
    auto genes = get_chromosome()->genes();

    m_metadata = calculate_enemie_genes_metadata(Singleton<EnemiesConfig>().get_instance(), genes);

    double fitness = 0;
    fitness += position_fitness(m_metadata);
    fitness += atributes_balance_fitness(m_metadata);
    return fitness;
}

double EnemyIndividual::position_fitness(const EnemieGenesMetadata& metadata) const
{
    double fitness = 0;
    for (auto enemy_count : metadata.enemy_count_by_room) {
        fitness += enemy_count >= enemies_config.enemy_count_by_room ? 2 : 0;
    }
    return fitness;
}

double EnemyIndividual::atributes_balance_fitness(const EnemieGenesMetadata& metadata) const
{
    double fitness = 0;
    for (auto& enemy_gene : metadata.enemy_metadata) {
        if (!enemy_gene.is_allocated) {
            continue;
        }
        fitness += (1 - enemy_gene.dmg_hlt_diff) + (1 - enemy_gene.cdw_vlt_diff);
    }

    double allowed_max_att = max_att * 4;
    for (auto& total_att : metadata.total_att_by_room) {
        fitness += 2 * (1.0 - (fdim(allowed_max_att, total_att) / allowed_max_att));
    }
    return fitness;
}

EnemieGenesMetadata EnemyIndividual::calculate_enemie_genes_metadata(const EnemiesConfig& enemies_config, const std::vector<EnemyGene>& genes)
{
    EnemieGenesMetadata metadata = {};
    assert(enemies_config.current_dungeon);

    metadata.enemies_config = enemies_config;
    metadata.enemy_count_by_room = std::vector<size_t>(enemies_config.current_dungeon->get_rooms().size(), 0);
    metadata.total_att_by_room = std::vector<uint32_t>(enemies_config.current_dungeon->get_rooms().size(), 0);
    metadata.enemy_metadata = std::vector<EnemyGeneMetadata>(genes.size());

    DungeonMatrix dm = enemies_config.current_dungeon->get_matrix();
    int i = 0;
    for (auto& gene : genes) {
        if (!dm.allocated_rooms().contains(gene.room)) {
            metadata.enemy_metadata[i].is_allocated = false;
            continue;
        }

        metadata.enemy_count_by_room[gene.room]++;
        metadata.enemy_metadata[i].is_allocated = true;
        metadata.enemy_metadata[i].dmg_hlt_diff = std::fdim(gene.damage, gene.health) / max_att;
        metadata.enemy_metadata[i].cdw_vlt_diff = std::fdim(gene.attackCooldown, gene.velocity) / max_att;
        metadata.total_att_by_room[gene.room] += gene.damage + gene.health + gene.attackCooldown + gene.velocity;
        i++;
    }

    return metadata;
}

void EnemyIndividual::report() const
{
    std::cout << "placed_enemies_count: " << m_metadata.enemy_metadata.size();

    double total_dmg_hlt_diff = 0;
    double total_cdw_vlt_diff = 0;
    for (auto enemy_metadata : m_metadata.enemy_metadata) {
        total_dmg_hlt_diff += enemy_metadata.dmg_hlt_diff;
        total_cdw_vlt_diff += enemy_metadata.cdw_vlt_diff;
    }
    std::cout << " | dmg_hlt_diff (average): " << total_dmg_hlt_diff / m_metadata.enemy_metadata.size()
              << " | cdw_vlt_diff (average): " << total_cdw_vlt_diff / m_metadata.enemy_metadata.size();

    double total_att_count = 0;
    for (auto total_att : m_metadata.total_att_by_room) {
        total_att_count += total_att;
    }
    std::cout << " | total_att_by_room (average): " << total_att_count / m_metadata.total_att_by_room.size();

    double total_enemies_count = 0;
    for (auto enemy_count : m_metadata.enemy_count_by_room) {
        total_enemies_count += enemy_count;
    }
    std::cout << " | enemy_count_by_room (average): " << total_enemies_count / m_metadata.enemy_count_by_room.size();

    std::cout << "\n";
}
