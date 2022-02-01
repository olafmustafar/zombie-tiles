#include "enemychormosome.h"

#include <models/dungeonconfig.hpp>
#include <utils/randomgenerator.hpp>

EnemyChormosome::EnemyChormosome()
    : enemies { std::vector<Enemy> { DungeonConfig::get_instance().get_rooms_count() * 2, Enemy {} } }

{
}

void EnemyChormosome::randomize()
{
    for (auto& e : enemies) {
        e.damage = Random::random_between(1, 100);
        e.health = Random::random_between(1, 100);
        e.velocity = Random::random_between(1, 100);
        e.attackCooldown = Random::random_between(1, 100);
    }
}

void EnemyChormosome::mutate()
{
    Enemy& e = enemies[Random::random_between(0, enemies.size() - 1)];
    e.damage = Random::random_between(1, 100);
    e.health = Random::random_between(1, 100);
    e.velocity = Random::random_between(1, 100);
    e.attackCooldown = Random::random_between(1, 100);
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
    string str = "enemyChormosome(";
    for (auto& e : enemies) {
        str += e.to_string();
    }
    str += ")";
    return str;
}
