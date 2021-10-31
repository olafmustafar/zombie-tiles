#include "door.hpp"

Door::Door() = default;

Door::Door(const Point& location, Orientation orientation)
    : location(location)
    , orientation(orientation)
{
}

bool Door::operator==(const Door& other) const
{
    return (this->location == other.location && this->orientation == other.orientation);
}
