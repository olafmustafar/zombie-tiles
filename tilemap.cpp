#include "tilemap.h"

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
