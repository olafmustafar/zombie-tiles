#include "room.h"

Room::Room(int x, int y, int width, int height, Room::PlacementType placement_type)
    : x(x), y(y), width(width), height(height), placement_type(placement_type)
{}

int Room::getX() const
{
    return x;
}

void Room::setX(int value)
{
    x = value;
}

int Room::getY() const
{
    return y;
}

void Room::setY(int value)
{
    y = value;
}

int Room::getWidth() const
{
    return width;
}

void Room::setWidth(int value)
{
    width = value;
}

int Room::getHeight() const
{
    return height;
}

void Room::setHeight(int value)
{
    height = value;
}

Room::PlacementType Room::getPlacement_type() const
{
    return placement_type;
}

void Room::setPlacement_type(const PlacementType &value)
{
    placement_type = value;
}
