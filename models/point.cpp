#include "point.hpp"

Point::Point()
    : Point(0, 0)
{
}

Point::Point(int x, int y)
    : x(x)
    , y(y)
{
}

bool Point::operator==(const Point& other) const
{
    return this->x == other.x
        && this->y == other.y;
}

bool Point::operator!=(const Point& other) const
{
    return !(*this == other);
}
