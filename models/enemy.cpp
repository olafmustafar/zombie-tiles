#include "enemy.hpp"
#include <sstream>
#include <string>

Enemy::Enemy()
    : Entity { EntityType::ENEMY, Point {} }
{
}

std::string Enemy::to_string() const
{
    std::ostringstream ss;
    ss << "enemy( ";
    ss << "position.x: " << position.x << "\n";
    ss << "position.y: " << position.y << "\n";
    ss << "health: " << health << "\n";
    ss << "damage: " << damage << "\n";
    ss << "attackCooldow: " << attackCooldown << "\n";
    ss << "velocity: " << velocity << ")" << std::endl;
    return ss.str();
}
