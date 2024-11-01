#pragma once

#include "room.hpp"
#include <cstdint>
#include <models/door.hpp>
#include <models/dungeonmatrix.hpp>
#include <models/enemy.hpp>
#include <models/entity.hpp>
#include <models/point.hpp>
#include <string>
#include <vector>

using namespace std;

class Dungeon {
public:
    static constexpr int EMPTY_ROOM = -1;
    static constexpr int PLAYER_ROOM = 0;

    Dungeon(const uint32_t width, const uint32_t height);
    Dungeon(const Dungeon& other);
    ~Dungeon();

    Dungeon& operator=(const Dungeon& other);
    Dungeon& operator=(Dungeon&& other) noexcept;
    int* operator[](const int index) const;
    int operator[](const Point& point) const;

    void add_room(const Room& room);
    const vector<Room>& rooms() const;
    vector<Room>& rooms();
    const vector<Room>& get_rooms() const;

    const Entity& get_player() const;
    void set_player(const Entity& player);

    void add_enemy(const Enemy& enemy);
    void set_enemies(const std::vector<Enemy>&& enemies);
    const vector<Enemy>& enemies() const;
    const vector<Enemy>& get_enemies() const;

    void add_door(const Door& room);
    const vector<Door>& get_doors() const;

    void clear();

    uint32_t width() const;
    uint32_t get_width() const;
    uint32_t height() const;
    uint32_t get_height() const;

    string to_string() const;

    const DungeonMatrix& get_matrix();
    std::optional<std::reference_wrapper<const DungeonMatrix>> get_matrix() const;

    bool has_enemies() const;

    bool has_player() const;
    void set_has_player(bool has_player);

private:
    uint32_t m_width;
    uint32_t m_height;
    DungeonMatrix m_matrix2;
    int** m_matrix;
    vector<Door> m_doors;
    Entity m_player;
    vector<Enemy> m_enemies;
    vector<Room> m_rooms;

    bool m_has_player;
    bool m_has_matrix;

    void initialize_matrix();
    void delete_matrix();
};
