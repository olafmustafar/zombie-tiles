#include "enemychormosome.h"

#include <models/dungeonconfig.hpp>
#include <models/enemiesconfig.hpp>
#include <utils/randomgenerator.hpp>
#include <utils/singleton.hpp>

EnemyChormosome::EnemyChormosome()
    : dungeon { *Singleton<EnemiesConfig>().get_instance().current_dungeon }
    , enemies { std::vector<Enemy> { DungeonConfig::get_instance().get_rooms_count() * 2, Enemy {} } }
    , min { Singleton<EnemiesConfig>().get_instance().min_att_value }
    , max { Singleton<EnemiesConfig>().get_instance().max_att_value }
{
}

void EnemyChormosome::randomize()
{
    for (auto& e : enemies) {
        e.position.x = Random::random_between(0, dungeon.get_width() - 1);
        e.position.y = Random::random_between(0, dungeon.get_height() - 1);
        e.damage = Random::random_between(min, max);
        e.health = Random::random_between(min, max);
        e.velocity = Random::random_between(min, max);
        e.attackCooldown = Random::random_between(min, max);
    }
}

void EnemyChormosome::mutate()
{
    for (size_t i = 0; i < (enemies.size() * 0.2); i++) {
        Enemy& e = enemies[Random::random_between(0, enemies.size() - 1)];
        e.position.x = Random::random_between(0, dungeon.get_width() - 1);
        e.position.y = Random::random_between(0, dungeon.get_height() - 1);
        e.damage = Random::random_between(min, max);
        e.health = Random::random_between(min, max);
        e.velocity = Random::random_between(min, max);
        e.attackCooldown = Random::random_between(min, max);
    }
}

void EnemyChormosome::crossover(Chromosome* other)
{
    EnemyChormosome* o_enemy = static_cast<EnemyChormosome*>(other);

    for (size_t i = 0; i < enemies.size(); i++) {
        if (i % 2 == 0) {
            swap(enemies[i], o_enemy->enemies[i]);
        }
    }
}

string EnemyChormosome::to_string() const
{
    std::string str = "enemyChormosome(";
    for (const auto& e : enemies) {
        str += e.to_string();
    }
    str += ")";
    return str;
}
