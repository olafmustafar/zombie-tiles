#include "room.h"
#include <iostream>

Room::Room() : x(0), y(0), width(0), height(0), placement_type(PlacementType::T) {}

Room::Room(int x, int y, int width, int height, Room::PlacementType placement_type)
    : x(x), y(y), width(width), height(height), placement_type(placement_type)
{}

int Room::get_x() const
{
    return x;
}

void Room::set_x(int value)
{
    x = value;
}

int Room::get_y() const
{
    return y;
}

void Room::set_y(int value)
{
    y = value;
}

int Room::get_width() const
{
    return width;
}

void Room::set_width(int value)
{
    width = value;
}

int Room::get_height() const
{
    return height;
}

void Room::set_height(int value)
{
    height = value;
}

Room::PlacementType Room::get_placement_type() const
{
    return placement_type;
}

void Room::set_placement_type(const PlacementType &value)
{
    placement_type = value;
}

void Room::print() const
{
    // clang-format off
    std::cout
            << "room ("
            << " width:" << get_width()
            << " height:" << get_height()
            << " x:" << get_x()
            << " y:" << get_y()
            << " placement:" << static_cast<int>(get_placement_type())
            << " )" << std::endl;
    // clang-format on
}
