#include "tilemap.hpp"
#include <helpers/roomhelper.hpp>
#include <iostream>

TileMap::TileMap(const uint32_t width, const uint32_t height)
    : m_width(width)
    , m_height(height)
    , m_map_matrix(nullptr)
    , m_doors {}
    , m_rooms {}
{
    m_map_matrix = new int*[m_width];
    for (uint32_t i = 0; i <= m_width; ++i) {
        m_map_matrix[i] = new int[m_height] {};
    }
}

TileMap::~TileMap()
{
    for (uint32_t i = 0; i <= m_width; ++i) {
        delete[] m_map_matrix[i];
    }
    delete[] m_map_matrix;
}

int* TileMap::operator[](const int index) const { return m_map_matrix[index]; }

void TileMap::addRoom(const Room new_room)
{
    if (!RoomHelper::check_if_can_add(new_room, m_rooms)) {
        return;
    }

    m_rooms.push_back(new_room);
    int index = m_rooms.size();

    for (uint32_t i = new_room.get_x(); i < new_room.get_x2(); ++i) {
        for (uint32_t j = new_room.get_y(); j < new_room.get_y2(); ++j) {
            int& current = m_map_matrix[i][j];

            if (current == EMPTY_ROOM || new_room.get_placement_type() == Room::PlacementType::T) {
                current = index;
            }
        }
    }
}

void TileMap::clear()
{
    for (uint32_t j = 0; j < m_height; ++j) {
        for (uint32_t i = 0; i < m_width; ++i) {
            m_map_matrix[i][j] = EMPTY_ROOM;
        }
    }
    m_rooms.clear();
}

uint32_t TileMap::get_width() const
{
    return m_width;
}

uint32_t TileMap::get_height() const
{
    return m_height;
}

const vector<Room>& TileMap::get_rooms() const
{
    return m_rooms;
}

string TileMap::to_string() const
{
    string str = "map( \n";
    for (const Room& room : m_rooms) {
        str += room.to_string() + '\n';
    }
    str += ")";
    return str;
}
