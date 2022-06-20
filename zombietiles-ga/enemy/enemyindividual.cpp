#include "enemyindividual.h"
#include "helpers/roommaphelper.hpp"
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

    auto enemies = get_chromosome()->enemies;

    double fitness = 0;

    std::vector<Enemy> allocated_enemies;

    const auto& matrix = enemies_config.current_dungeon->get_matrix();
    for (auto& enemy : enemies) {
        if (matrix[enemy.position] != Dungeon::EMPTY_ROOM
            && matrix[enemy.position] != Dungeon::PLAYER_ROOM) {
            allocated_enemies.push_back(enemy);
        }
    }

    m_metadata = RoomMapHelper::calculate_enemies_metadata(enemies_config, allocated_enemies);
    fitness += position_fitness(m_metadata);
    fitness += atributes_balance_fitness(m_metadata);
    return fitness;
}

double EnemyIndividual::position_fitness(const EnemiesMetadata& metadata) const
{
    double fitness = 0;
    for (auto& enemy_count : metadata.enemy_count_by_room) {
        fitness += enemy_count >= enemies_config.enemy_count_by_room ? 2 : 0;
    }
    return fitness;
}

double EnemyIndividual::atributes_balance_fitness(const EnemiesMetadata& metadata) const
{
    double fitness = 0;

    for (EnemyMetadata e : metadata.enemy_metadata) {
        fitness += std::fdim(e.dmg_hlt_diff, e.cdw_vlt_diff) * 2;
    }

    for (auto sum : metadata.total_att_by_room) {
        fitness += 1.0 - (fdim(max_att * 4, sum) / (max_att * 4));
    }

    return fitness;
}

void EnemyIndividual::report() const
{
    std::cout << "placed_enemies_count: " << m_metadata.enemy_metadata.size();

    int i = 0;
    for (auto enemy_metadata : m_metadata.enemy_metadata) {
        std::cout << " | dmg_hlt_diff[" << i << "]: " << enemy_metadata.dmg_hlt_diff
                  << " | cdw_vlt_diff[" << i << "]: " << enemy_metadata.cdw_vlt_diff;
        i++;
    }

    for (auto total_att : m_metadata.total_att_by_room) {
        std::cout << " | total_att_by_room[" << i << "]: " << total_att;
        i++;
    }

    i = 0;
    for (auto total_att : m_metadata.enemy_count_by_room) {
        std::cout << " | enemy_count_by_room[" << i << "]: " << total_att;
        i++;
    }

    std::cout << "\n";
}
