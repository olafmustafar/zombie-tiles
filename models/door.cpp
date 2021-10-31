#include "door.hpp"

Door::Door() = default;

Door::Door(const Point& location, Orientation orientation)
    : location(location)
    , orientation(orientation)
{
}
