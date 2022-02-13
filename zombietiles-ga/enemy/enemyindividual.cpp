#include "enemyindividual.h"
#include <cmath>
#include <models/enemiesconfig.hpp>
#include <utils/globalutils.hpp>
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

double EnemyIndividual::calculate_fitness() const
{
    auto& dungeon = *enemies_config.current_dungeon;
    auto enemies = get_chromosome()->enemies;

    double fitness = 0;

    std::vector<Enemy> allocated_enemies;

    for (auto& enemy : enemies) {
        if (dungeon[enemy.position] != RoomMap::EMPTY_ROOM
            && dungeon[enemy.position] != RoomMap::PLAYER_ROOM) {
            allocated_enemies.push_back(enemy);
        }
    }

    fitness += position_fitness(allocated_enemies);

    fitness += atributes_balance_fitness(allocated_enemies);

    return fitness;
}

double EnemyIndividual::position_fitness(const std::vector<Enemy>& enemies) const
{
    auto& dungeon = *enemies_config.current_dungeon;
    double fitness = 0;

    std::vector<size_t> enemy_count_by_room(dungeon.get_rooms().size(), 0);
    for (auto& enemy : enemies) {
        enemy_count_by_room[dungeon[enemy.position]]++;
    }

    for (auto& enemy_count : enemy_count_by_room) {
        fitness += max(0.0, 2 - fdim(enemy_count, enemies_config.enemy_count_by_room));
    }

    return fitness;
}

double EnemyIndividual::atributes_balance_fitness(const std::vector<Enemy>& enemies) const
{
    double fitness = 0;
    for (auto& enemy : enemies) {
        auto dmg_hlt_diff = std::max(1.0 - (std::fdim(enemy.damage, enemy.health) / max_att), 0.0);
        auto cdw_vlt_diff = std::max(1.0 - (std::fdim(enemy.attackCooldown, enemy.velocity) / max_att), 0.0);
        fitness += std::fdim(dmg_hlt_diff, cdw_vlt_diff) * 2;

        auto sum = enemy.damage + enemy.damage + enemy.attackCooldown + enemy.velocity;
        fitness += 1.0 - (fdim(max_att * 4, sum) / (max_att * 4));
    }
    return fitness;
}
