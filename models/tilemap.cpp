#include "tilemap.h"
#include <algorithm>
#include <functional>
#include <helpers/roomhelper.h>
#include <iostream>

TileMap::TileMap(const uint32_t width, const uint32_t height)
    : m_width(width)
    , m_height(height)
{
    m_map_matrix = new int*[m_width];
    for (uint32_t i = 0; i <= m_width; ++i) {
        m_map_matrix[i] = new int[m_height];
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

void TileMap::addRoom(const Room& newRoom)
{
    auto overlaps_with_new_room = bind(&RoomHelper::check_if_2_rooms_overlap, placeholders::_1, newRoom);
    if (m_rooms.size() && !any_of(m_rooms.cbegin(), m_rooms.cend(), overlaps_with_new_room)) {
        return;
    }

    m_rooms.push_back(newRoom);
    int index = m_rooms.size();

    for (uint32_t i = 0; i < newRoom.get_width(); ++i) {
        for (uint32_t j = 0; j < newRoom.get_height(); ++j) {
            int& current = m_map_matrix[i + newRoom.get_x()][j + newRoom.get_y()];

            if (current == EMPTY_ROOM || newRoom.get_placement_type() == Room::PlacementType::T) {
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
    string str = "";

    for (uint32_t j = 0; j < m_height; ++j) {
        for (uint32_t i = 0; i < m_width; ++i) {
            if (m_map_matrix[i][j] == EMPTY_ROOM) {
                if (i == 0) {
                    str += "|  ";
                } else if (i == m_width - 1) {
                    str += "  |";
                } else {
                    str += "   ";
                }
                continue;
            }

            str += "[" + std::to_string(m_map_matrix[i][j]) + "]";
        }

        str += "\n";
    }
    return str;
}
