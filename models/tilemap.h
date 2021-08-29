#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include "room.h"

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

    void addRoom(const Room& room);

    string to_string() const;

private:
    const uint32_t m_width;
    const uint32_t m_height;
    int** m_map_matrix;
    vector<Door> m_doors;
    vector<Room> m_rooms;
};
