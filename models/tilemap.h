#pragma once

#include <cstdint>
#include <vector>

using namespace std;

struct Door
{
    uint32_t x;
    uint32_t y;
};

class TileMap
{
public:
    TileMap(const uint32_t width, const uint32_t height);
    ~TileMap();
    int* operator[](const int index) const;

private:
    const uint32_t m_width;
    const uint32_t m_height;
    int** m_map_matrix;
    vector<Door> m_doors;
};
