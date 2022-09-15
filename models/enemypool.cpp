#include "enemypool.hpp"
#include "enemiesconfig.hpp"
#include <utils/randomgenerator.hpp>
#include <utils/singleton.hpp>

EnemyPool EnemyPool::make_enemy_pool(size_t pool_size)
{
    EnemyPool ep {};
    for (size_t i = 0; i < pool_size; i++) {
        ep.push_back(Enemy {
            Random::random_between(St<EnemiesConfig>.min_att, St<EnemiesConfig>.max_att),
            Random::random_between(St<EnemiesConfig>.min_att, St<EnemiesConfig>.max_att),
            Random::random_between(St<EnemiesConfig>.min_att, St<EnemiesConfig>.max_att),
            Random::random_between(St<EnemiesConfig>.min_att, St<EnemiesConfig>.max_att),
        });
    }
    return ep;
}
