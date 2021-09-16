#include "tilemap.h"
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

void TileMap::addRoom(const Room& new_room)
{
    if (!RoomHelper::check_if_can_add(new_room, m_rooms)) {
        return;
    }

    m_rooms.push_back(new_room);
    int index = m_rooms.size();

    for (uint32_t i = 0; i < new_room.get_width(); ++i) {
        for (uint32_t j = 0; j < new_room.get_height(); ++j) {
            int& current = m_map_matrix[i + new_room.get_x()][j + new_room.get_y()];

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
    string str = "     ";
    {
        string linha = "     ";
        for (uint32_t i = 0; i < m_width; ++i) {
            char buffer[255];
            sprintf(buffer, "%3d", i);
            str += buffer;
            linha += "___";
        }
        str += "\n" + linha + "\n";
    }

    for (uint32_t j = 0; j < m_height; ++j) {
        for (uint32_t i = 0; i < m_width; ++i) {
            if (i == 0) {
                char buffer[255];
                sprintf(buffer, "% 3d |", j);
                str += buffer;
            }

            if (m_map_matrix[i][j] == EMPTY_ROOM) {
                str += "   ";
            } else {
                str += "[" + std::to_string(m_map_matrix[i][j]) + "]";
            }

            if (i == m_width - 1) {
                str += "|";
            }
        }

        str += "\n";
    }
    return str;
}
