#pragma once

#include "point.hpp"

enum class EntityType {
    PLAYER,
    ENEMY,
};

struct Entity {
    EntityType type;
    Point position;
};
