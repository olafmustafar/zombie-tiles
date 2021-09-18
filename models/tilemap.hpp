#pragma once

#include "room.hpp"
#include <cstdint>
#include <string>
#include <vector>

using namespace std;

struct Door {
    uint32_t x;
    uint32_t y;
};

class TileMap {
public:
    static constexpr int EMPTY_ROOM = 0;

    TileMap(const uint32_t width, const uint32_t height);
    ~TileMap();
    int* operator[](const int index) const;

    void addRoom(const Room& room);
    void clear();

    uint32_t get_width() const;
    uint32_t get_height() const;
    const vector<Room>& get_rooms() const;

    string to_string() const;

private:
    const uint32_t m_width;
    const uint32_t m_height;
    int** m_map_matrix;
    vector<Door> m_doors;
    vector<Room> m_rooms;
};
