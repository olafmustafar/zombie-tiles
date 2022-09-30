#include "dungeon.hpp"
#include <algorithm>
#include <functional>
#include <helpers/roomhelper.hpp>
#include <helpers/roommaphelper.hpp>
#include <iostream>
#include <optional>

using namespace std;

Dungeon::Dungeon(const uint32_t width, const uint32_t height)
    : m_width(width)
    , m_height(height)
    , m_matrix2 { width, height }
    , m_matrix { nullptr }
    , m_doors {}
    , m_enemies {}
    , m_rooms {}
    , m_has_player { false }
    , m_has_matrix { false }
{
    initialize_matrix();
}

Dungeon::Dungeon(const Dungeon& other)
    : Dungeon(other.get_width(), other.get_height())
{
    *this = other;
}

Dungeon::~Dungeon()
{
    if (!m_matrix) {
        return;
    }

    delete_matrix();
}

Dungeon& Dungeon::operator=(const Dungeon& other)
{
    if (this == &other) {
        return *this;
    }

    if (m_width != other.m_width || m_height != other.m_height) {
        delete_matrix();
        m_width = other.m_width;
        m_height = other.m_height;
        initialize_matrix();
    }

    m_rooms = other.m_rooms;
    m_doors = other.m_doors;

    for (uint32_t i = 0; i < m_width; ++i) {
        for (uint32_t j = 0; j < m_height; ++j) {
            m_matrix[i][j] = other[i][j];
        }
    }

    return *this;
}

Dungeon& Dungeon::operator=(Dungeon&& other) noexcept
{
    if (this == &other) {
        return *this;
    }

    delete_matrix();

    m_width = other.m_width;
    m_height = other.m_height;
    m_rooms = std::move(other.m_rooms);
    m_doors = std::move(other.m_doors);
    m_matrix = other.m_matrix;

    other.m_width = 0;
    other.m_height = 0;
    other.m_rooms = {};
    other.m_doors = {};
    other.m_matrix = nullptr;
    return *this;
}

int* Dungeon::operator[](const int index) const { return m_matrix[index]; }

int Dungeon::operator[](const Point& point) const { return m_matrix[point.x][point.y]; }

void Dungeon::add_room(const Room& new_room)
{
    m_rooms.push_back(new_room);
    int index = m_rooms.size() - 1;

    for (uint32_t i = new_room.get_x(); i < new_room.get_x2(); ++i) {
        for (uint32_t j = new_room.get_y(); j < new_room.get_y2(); ++j) {
            int& current = m_matrix[i][j];

            if (current == EMPTY_ROOM || new_room.get_placement_type() == Room::PlacementType::T) {
                current = index;
            }
        }
    }
}

const vector<Room>& Dungeon::rooms() const { return m_rooms; }
vector<Room>& Dungeon::rooms() { return m_rooms; }

void Dungeon::add_enemy(const Enemy& enemy)
{
    m_enemies.push_back(enemy);
}

void Dungeon::set_enemies(const std::vector<Enemy>&& enemies){
    m_enemies = enemies;
}

const vector<Enemy>& Dungeon::enemies() const { return m_enemies; }

const vector<Enemy>& Dungeon::get_enemies() const { return m_enemies; }

void Dungeon::add_door(const Door& door) { m_doors.push_back(door); }

const vector<Door>& Dungeon::get_doors() const { return m_doors; }

void Dungeon::clear()
{
    for (uint32_t j = 0; j < m_height; ++j) {
        for (uint32_t i = 0; i < m_width; ++i) {
            m_matrix[i][j] = EMPTY_ROOM;
        }
    }
    m_rooms.clear();
}

uint32_t Dungeon::width() const { return m_width; }

uint32_t Dungeon::get_width() const { return m_width; }

uint32_t Dungeon::height() const { return m_height; }

uint32_t Dungeon::get_height() const { return m_height; }

const vector<Room>& Dungeon::get_rooms() const { return m_rooms; }

string Dungeon::to_string() const
{
    string str = "map( \n";
    for (const Room& room : m_rooms) {
        str += room.to_string() + '\n';
    }
    str += ")";
    return str;
}

const DungeonMatrix& Dungeon::get_matrix()
{
    if (!m_has_matrix && !m_rooms.empty()) {
        m_matrix2 = RoomMapHelper::generate_dungeon_matrix(*this);
        m_has_matrix = true;
    }
    return m_matrix2;
}

std::optional<std::reference_wrapper<const DungeonMatrix>> Dungeon::get_matrix() const
{
    if( m_has_matrix ){
        return m_matrix2;
    } 
    return std::nullopt;
}

const Entity& Dungeon::get_player() const { return m_player; }

void Dungeon::set_player(const Entity& player)
{
    this->m_player = player;
    m_has_player = true;
}

bool Dungeon::has_enemies() const { return !m_enemies.empty(); }

bool Dungeon::has_player() const { return m_has_player; }

void Dungeon::set_has_player(bool has_player) { m_has_player = has_player; }

void Dungeon::initialize_matrix()
{
    m_matrix = new int*[m_width];
    for (uint32_t i = 0; i < m_width; ++i) {
        m_matrix[i] = new int[m_height] {};
        std::fill_n(m_matrix[i], m_height, -1);
    }
}

void Dungeon::delete_matrix()
{
    for (uint32_t i = 0; i < m_width; ++i) {
        delete[] m_matrix[i];
    }
    delete[] m_matrix;
}
