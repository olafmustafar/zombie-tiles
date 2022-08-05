#include "enemyindividual.h"
#include "helpers/roommaphelper.hpp"
#include "models/dungeon.hpp"
#include "models/dungeonconfig.hpp"
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
    fitness += fitness_from_position(m_metadata);
    /* fitness += fitness_from_individual_balance(m_metadata); */
    fitness += fitness_from_room_balance(m_metadata);
    return fitness;
}

double EnemyIndividual::fitness_from_position(EnemieGenesMetadata& metadata) const
{
    double enemy_count_by_room = St<EnemiesConfig>.enemy_count_by_room;
    double room_fitness_sum = 0;
    for (auto enemy_count : metadata.enemy_count_by_room) {
        room_fitness_sum += enemy_count >= ( enemy_count_by_room / 2 ) ? 1: 0;
    }

    const double possible_total = DungeonConfig::get_instance().get_rooms_count();
    const double fitness = room_fitness_sum / possible_total;

    metadata.fitness_from_postition = fitness;

    return fitness;
}

/* double EnemyIndividual::fitness_from_position(EnemieGenesMetadata& metadata) const */
/* { */
/*     double room_fitness_sum = 0; */
/*     for (auto enemy_count : metadata.enemy_count_by_room) { */
/*         if (enemy_count == 0) { */
/*             continue; */
/*         } */
/*         room_fitness_sum += std::log(enemy_count); */
/*     } */

/*     const double possible_total = std::log(St<EnemiesConfig>.enemy_count_by_room) * DungeonConfig::get_instance().get_rooms_count(); */
/*     const double fitness = room_fitness_sum / possible_total; */

/*     metadata.fitness_from_postition = fitness; */

/*     return fitness; */
/* } */

double EnemyIndividual::fitness_from_individual_balance(EnemieGenesMetadata& metadata) const
{
    double fitness = 0;
    for (auto& enemy_gene : metadata.enemy_metadata) {
        if (!enemy_gene.is_allocated) {
            continue;
        }
        fitness += 1 - ((enemy_gene.dmg_hlt_diff + enemy_gene.cdw_vlt_diff) / 2);
    }

    fitness = fitness / metadata.enemy_metadata.size();

    metadata.fitness_from_individual_att_balance = fitness;

    return fitness;
}

double EnemyIndividual::fitness_from_room_balance(EnemieGenesMetadata& metadata) const
{
    const double total_allowed_per_enemy = max_att * 4;
/*     const double total_allowed_per_enemy = max_att * 4; */
    const double total_desired_per_room = ( total_allowed_per_enemy * enemies_config.enemy_count_by_room ) / 2;

    double fitness = 0;
    for (size_t i = 0; i < metadata.total_att_by_room.size(); i++) {
        const double enemy_count = metadata.enemy_count_by_room[i];

        //soma total dos atributos de cada inimigo e a soma total dos atributos desejados
        const double total_att_per_enemy = metadata.total_att_by_room[i] / enemy_count;
        const double total_desired_per_enemy = total_desired_per_room / enemy_count;

        //a diferenca entre os atributos desejados e o disponivel
        const double desired_and_actual_att_diference_per_enemy = positive_difference(total_att_per_enemy, total_desired_per_enemy);

        //diferenca total dividida pelo total possivel
        fitness += 1 - (desired_and_actual_att_diference_per_enemy / total_allowed_per_enemy);
    }

    fitness = fitness / metadata.total_att_by_room.size();

    metadata.fitness_from_room_att_balance = fitness;

    return fitness;
}

EnemieGenesMetadata EnemyIndividual::calculate_enemie_genes_metadata(const EnemiesConfig& enemies_config, const std::vector<EnemyGene>& genes)
{
    EnemieGenesMetadata metadata = {};
    assert(enemies_config.current_dungeon);

    metadata.fitness_from_postition = 0;
    metadata.fitness_from_individual_att_balance = 0;
    metadata.fitness_from_room_att_balance = 0;
    metadata.enemy_count_by_room = std::vector<size_t>(enemies_config.current_dungeon->get_rooms().size(), 0);
    metadata.total_att_by_room = std::vector<uint32_t>(enemies_config.current_dungeon->get_rooms().size(), 0);
    metadata.enemy_metadata = std::vector<EnemyGeneMetadata>(genes.size());

    DungeonMatrix dm = enemies_config.current_dungeon->get_matrix();
    int i = 0;
    for (auto& gene : genes) {
        if (!dm.allocated_rooms().contains(gene.room)) {
            metadata.enemy_metadata[i].is_allocated = false;
            metadata.enemy_count_by_room[gene.room] = 0;
            continue;
        }

        metadata.enemy_count_by_room[gene.room]++;
        metadata.enemy_metadata[i].is_allocated = true;
        metadata.enemy_metadata[i].dmg_hlt_diff = positive_difference(gene.damage, gene.health) / max_att;
        metadata.enemy_metadata[i].cdw_vlt_diff = positive_difference(gene.attackCooldown, gene.velocity) / max_att;
        metadata.total_att_by_room[gene.room] += gene.damage + gene.health + gene.attackCooldown + gene.velocity;
        i++;
    }

    return metadata;
}

void EnemyIndividual::report() const
{
    std::cout << "placed_enemies_count: " << m_metadata.enemy_metadata.size();

    /* double total_cdw_vlt_diff = 0; */
    /* for (auto enemy_metadata : m_metadata.enemy_metadata) { */
    /*     if (!enemy_metadata.is_allocated) { */
    /*         std::cout << " | dmg_hlt_diff[" << i << "]: not allocated" */
    /*                   << " | cdw_vlt_diff[" << i << "]: not allocated"; */
    /*     } */
    /*     std::cout << " | dmg_hlt_diff[" << i << "]: " << enemy_metadata.dmg_hlt_diff */
    /*               << " | cdw_vlt_diff[" << i << "]: " << enemy_metadata.cdw_vlt_diff; */

    /*     total_dmg_hlt_diff += enemy_metadata.dmg_hlt_diff; */
    /*     total_cdw_vlt_diff += enemy_metadata.cdw_vlt_diff; */
    /*     i++; */
    /* } */
    /* std::cout << " | dmg_hlt_diff (average): " << total_dmg_hlt_diff / m_metadata.enemy_metadata.size() */
    /*           << " | cdw_vlt_diff (average): " << total_cdw_vlt_diff / m_metadata.enemy_metadata.size(); */

    double total_att_count = 0;
    int i = 0;
    for (auto total_att : m_metadata.total_att_by_room) {
        std::cout << " | total_att_by_room[" << i << "] : " << total_att;
        total_att_count += total_att;
        i++;
    }
    std::cout << " | total_att_by_room (average): " << total_att_count / m_metadata.total_att_by_room.size();

    double total_enemies_count = 0;
    i = 0;
    for (auto enemy_count : m_metadata.enemy_count_by_room) {
        std::cout << " | enemy_count_by_room[" << i << "]: " << enemy_count;
        total_enemies_count += enemy_count;
        i++;
    }
    std::cout << " | enemy_count_by_room (average): " << total_enemies_count / m_metadata.enemy_count_by_room.size();

    std::cout << " | fitness_from_postition " << m_metadata.fitness_from_postition;
    std::cout << " | fitness_from_room_att_balance " << m_metadata.fitness_from_room_att_balance;

    std::cout << "\n";
}

double EnemyIndividual::positive_difference(double a, double b)
{
    return a >= b ? a - b : b - a;
}
