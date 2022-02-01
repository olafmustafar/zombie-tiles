#pragma once

#include "entity.hpp"
#include <string>

struct Enemy : Entity {
    Enemy();

    float health;
    float damage;
    float attackCooldown;
    float velocity;

    std::string to_string() const;
};
