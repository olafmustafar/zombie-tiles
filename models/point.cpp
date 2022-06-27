#include "point.hpp"

Point::Point()
    : Point(0, 0)
{
}

Point::Point(size_t x, size_t y)
    : Point { static_cast<int>(x), static_cast<int>(y) }
{
}

Point::Point(int x, int y)
    : x(x)
    , y(y)
{
}

Point::Point(uint32_t x, uint32_t y)
    : Point { static_cast<int>(x), static_cast<int>(y) }
{
}

Point operator-(const Point& lhs, const Point& rhs)
{
    return { lhs.x - rhs.x, lhs.y - rhs.y };
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
