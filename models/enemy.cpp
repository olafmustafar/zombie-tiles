#include "enemy.hpp"
#include <sstream>

Enemy::Enemy()
    : Entity { EntityType::ENEMY, Point {} }
{
}

std::string Enemy::to_string() const
{
    std::ostringstream ss;
    ss << "enemy( ";
    ss << "health: " << health << "\n";
    ss << "damage: " << damage << "\n";
    ss << "attackCooldow: " << attackCooldown << "\n";
    ss << "velocity: " << velocity << ")";

    return ss.str();
}
