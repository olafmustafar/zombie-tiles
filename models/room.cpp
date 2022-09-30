#include "room.hpp"
#include <iostream>

Room::Room()
    : x(0)
    , y(0)
    , width(0)
    , height(0)
    , placement_type(PlacementType::T)
    , is_placed(false)
{
}

Room::Room(
    uint32_t x, uint32_t y, uint32_t width, uint32_t height, Room::PlacementType placement_type)
    : x(x)
    , y(y)
    , width(width)
    , height(height)
    , placement_type(placement_type)
    , is_placed(false)
{
}

uint32_t Room::get_x() const
{
    return x;
}

void Room::set_x(uint32_t value)
{
    x = value;
}

uint32_t Room::get_y() const
{
    return y;
}

void Room::set_y(uint32_t value)
{
    y = value;
}

uint32_t Room::get_width() const
{
    return width;
}

void Room::set_width(uint32_t value)
{
    width = value;
}

uint32_t Room::get_height() const
{
    return height;
}

void Room::set_height(uint32_t value)
{
    height = value;
}

Room::PlacementType Room::get_placement_type() const
{
    return placement_type;
}

uint32_t Room::get_x2() const
{
    return x + width;
}

uint32_t Room::get_y2() const
{
    return y + height;
}

void Room::set_placement_type(const PlacementType& value)
{
    placement_type = value;
}

void Room::print() const
{
    std::cout
        << "room ("
        << " width:" << get_width()
        << " height:" << get_height()
        << " x:" << get_x()
        << " y:" << get_y()
        << " placement:" << static_cast<int>(get_placement_type())
        << " )" << std::endl;
}

string Room::to_string() const
{
    string str = "";
    str += "room (";
    str += " x:" + std::to_string(get_x());
    str += " y:" + std::to_string(get_y());
    str += " width:" + std::to_string(get_width());
    str += " height:" + std::to_string(get_height());
    str += " placement:" + std::to_string(static_cast<int>(get_placement_type()));
    str += " )";
    return str;
}
