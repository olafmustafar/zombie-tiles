#pragma once

struct Direction {
public:
    enum : int {
        UP = 0,
        RIGHT = 1,
        DOWN = 2,
        LEFT = 3,
    } value;

private:
    using m_DirectionEnum = decltype(Direction::value);

public:
    Direction(m_DirectionEnum value);
    operator m_DirectionEnum();
    bool operator==(m_DirectionEnum other);
    bool operator!=(m_DirectionEnum other);

    void turn_right();
    void turn_left();
};
