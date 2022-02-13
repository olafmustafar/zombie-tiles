#pragma once

#include "entity.hpp"
#include <string>

struct Enemy : Entity {
    Enemy();

    uint32_t health;
    uint32_t damage;
    uint32_t attackCooldown;
    uint32_t velocity;

    std::string to_string() const;
};
