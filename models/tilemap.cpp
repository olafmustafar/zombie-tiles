#include "tilemap.h"

namespace {
constexpr int EMPTY_ROOM = 0;
}

TileMap::TileMap(const uint32_t width, const uint32_t height) : m_width(width), m_height(height)
{
    m_map_matrix = new int*[m_width];
    for (uint32_t i = 0; i <= width; ++i) {
        m_map_matrix[i] = new int[height];
    }
}

TileMap::~TileMap()
{
    for (uint32_t i = 0; i <= m_width; ++i) {
        delete[] m_map_matrix[i];
    }
    delete[] m_map_matrix;
}

int* TileMap::operator[](const int index) const
{
    return m_map_matrix[index];
}

void TileMap::addRoom(const Room& room)
{
    m_rooms.push_back(room);
    int index = m_rooms.size();

    for (uint32_t i = 0; i < room.get_width(); ++i) {
        for (uint32_t j = 0; j < room.get_height(); ++j) {

            int& current = m_map_matrix[i + room.get_x()][j + room.get_y()];

            if (current == EMPTY_ROOM || room.get_placement_type() == Room::PlacementType::T) {
                current = index;
            }
        }
    }
}
