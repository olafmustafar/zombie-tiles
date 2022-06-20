#pragma once

#include "models/enemiesconfig.hpp"
#include <cstdint>
#include <vector>

struct EnemyMetadata {
    double dmg_hlt_diff;
    double cdw_vlt_diff;
};

struct EnemiesMetadata {
    EnemiesConfig enemies_config;
    std::vector<EnemyMetadata> enemy_metadata;
    std::vector<uint32_t> total_att_by_room;
    std::vector<size_t> enemy_count_by_room;
};
