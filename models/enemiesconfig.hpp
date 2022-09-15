#pragma once

#include <models/dungeon.hpp>

struct EnemiesConfig {
    EnemiesConfig();
    Dungeon* current_dungeon;
    uint32_t enemy_count_by_room;
    uint32_t max_att;
    uint32_t min_att;
};
