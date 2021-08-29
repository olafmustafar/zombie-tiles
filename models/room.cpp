#include "room.h"
#include <iostream>

Room::Room() : m_x(0), m_y(0), m_width(0), m_height(0), m_placement_type(PlacementType::T) {}

Room::Room(
        uint32_t x, uint32_t y, uint32_t width, uint32_t height, Room::PlacementType placement_type)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_placement_type(placement_type)
{}

uint32_t Room::get_x() const
{
    return m_x;
}

void Room::set_x(uint32_t value)
{
    m_x = value;
}

uint32_t Room::get_y() const
{
    return m_y;
}

void Room::set_y(uint32_t value)
{
    m_y = value;
}

uint32_t Room::get_width() const
{
    return m_width;
}

void Room::set_width(uint32_t value)
{
    m_width = value;
}

uint32_t Room::get_height() const
{
    return m_height;
}

void Room::set_height(uint32_t value)
{
    m_height = value;
}

Room::PlacementType Room::get_placement_type() const
{
    return m_placement_type;
}

void Room::set_placement_type(const PlacementType &value)
{
    m_placement_type = value;
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

string Room::to_string() const
{
    string str = "";
    str += "room (";
    str += " width:" + std::to_string(get_width());
    str += " height:" + std::to_string(get_height());
    str += " x:" + std::to_string(get_x());
    str += " y:" + std::to_string(get_y());
    str += " placement:" + std::to_string(static_cast<int>(get_placement_type()));
    str += " )";
    return str;
}
