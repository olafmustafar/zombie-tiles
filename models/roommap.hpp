#pragma once

#include "room.hpp"
#include <cstdint>
#include <models/door.hpp>
#include <models/enemy.hpp>
#include <models/point.hpp>
#include <string>
#include <vector>

using namespace std;

class RoomMap {
public:
    static constexpr int EMPTY_ROOM = -1;

    RoomMap(const uint32_t width, const uint32_t height);
    RoomMap(const RoomMap& other);
    ~RoomMap();

    RoomMap& operator=(const RoomMap& other);
    RoomMap& operator=(RoomMap&& other) noexcept;
    int* operator[](const int index) const;
    int operator[](const Point& point) const;

    void add_room(const Room& room);
    const vector<Room>& get_rooms() const;

    void add_enemy(const Enemy& enemy);
    const vector<Enemy>& get_enemies() const;

    void add_door(const Door& room);
    const vector<Door>& get_doors() const;

    void clear();

    uint32_t get_width() const;
    uint32_t get_height() const;

    string to_string() const;

    int** get_matrix() const;

private:
    uint32_t m_width;
    uint32_t m_height;
    int** m_matrix;
    vector<Door> m_doors;
    vector<Room> m_rooms;
    vector<Enemy> m_enemies;

    void initialize_matrix();
    void delete_matrix();
};
