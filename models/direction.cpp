#include "direction.hpp"

Direction::Direction(m_DirectionEnum value)
    : value(value)
{
}

bool Direction::operator==(m_DirectionEnum other) { return value == other; }

bool Direction::operator!=(m_DirectionEnum other) { return value != other; }

Direction::operator m_DirectionEnum() { return value; }

void Direction::turn_right()
{
    value = static_cast<m_DirectionEnum>((value + 5) % 4);
}

void Direction::turn_left()
{
    value = static_cast<m_DirectionEnum>((value + 3) % 4);
}
