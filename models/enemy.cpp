#include "enemy.hpp"
#include <sstream>
#include <string>

Enemy::Enemy()
    : Enemy { Point { 0, 0 }, 0, 0, 0, 0 }
{
}

Enemy::Enemy(Point point, uint32_t health, uint32_t damage, uint32_t attackCooldown, uint32_t velocity)
    : Entity { EntityType::ENEMY, Point { point } }
    , health { health }
    , damage { damage }
    , attackCooldown { attackCooldown }
    , velocity { velocity }
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
