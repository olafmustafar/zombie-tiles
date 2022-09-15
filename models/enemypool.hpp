#pragma once

#include "models/enemy.hpp"
#include <vector>

struct EnemyPool : std::vector<Enemy> {
    static EnemyPool make_enemy_pool(size_t pool_size);
};
