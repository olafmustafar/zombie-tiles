#pragma once

#include "room.hpp"
#include <cstdint>
#include <models/door.hpp>
#include <models/enemy.hpp>
#include <models/entity.hpp>
#include <models/point.hpp>
#include <string>
#include <vector>

using namespace std;

class RoomMap {
public:
    static constexpr int EMPTY_ROOM = -1;
    static constexpr int PLAYER_ROOM = 0;

    RoomMap(const uint32_t width, const uint32_t height);
    RoomMap(const RoomMap& other);
    ~RoomMap();

    RoomMap& operator=(const RoomMap& other);
    RoomMap& operator=(RoomMap&& other) noexcept;
    int* operator[](const int index) const;
    int operator[](const Point& point) const;

    void add_room(const Room& room);
    const vector<Room>& rooms() const;
    const vector<Room>& get_rooms() const;

    const Entity& get_player() const;
    void set_player(const Entity& player);

    void add_enemy(const Enemy& enemy);
    const vector<Enemy>& get_enemies() const;

    void add_door(const Door& room);
    const vector<Door>& get_doors() const;

    void clear();

    uint32_t width() const;
    uint32_t get_width() const;
    uint32_t height() const;
    uint32_t get_height() const;

    string to_string() const;

    int** get_matrix() const;

    bool has_entities() const;

    bool has_player() const;
    void set_has_player(bool has_player);

private:
    uint32_t m_width;
    uint32_t m_height;
    int** m_matrix;
    vector<Door> m_doors;
    Entity m_player;
    vector<Enemy> m_enemies;
    vector<Room> m_rooms;

    bool m_has_enemies;
    bool m_has_player;

    void initialize_matrix();
    void delete_matrix();
};
