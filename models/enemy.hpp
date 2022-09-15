#pragma once

#include "entity.hpp"
#include <string>

struct Enemy : Entity {
    Enemy();
    Enemy(Point point, uint32_t health, uint32_t damage, uint32_t attackCooldown, uint32_t velocity);
    Enemy(uint32_t health, uint32_t damage, uint32_t attackCooldown, uint32_t velocity);

    uint32_t health;
    uint32_t damage;
    uint32_t attackCooldown;
    uint32_t velocity;

    std::string to_string() const;
};
