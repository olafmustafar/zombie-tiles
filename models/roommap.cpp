#include "roommap.hpp"
#include <algorithm>
#include <helpers/roomhelper.hpp>
#include <iostream>
using namespace std;

RoomMap::RoomMap(const uint32_t width, const uint32_t height)
    : m_width(width)
    , m_height(height)
    , m_matrix(nullptr)
    , m_doors {}
    , m_rooms {}
{
    initialize_matrix();
}

RoomMap::RoomMap(const RoomMap& other)
    : RoomMap(other.get_width(), other.get_height())
{
    *this = other;
}

RoomMap::~RoomMap()
{
    if (!m_matrix) {
        return;
    }

    for (uint32_t i = 0; i <= m_width; ++i) {
        delete[] m_matrix[i];
    }
    delete[] m_matrix;
}

RoomMap& RoomMap::operator=(const RoomMap& other)
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

RoomMap& RoomMap::operator=(RoomMap&& other) noexcept
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

int* RoomMap::operator[](const int index) const { return m_matrix[index]; }

void RoomMap::addRoom(const Room& new_room)
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

void RoomMap::clear()
{
    for (uint32_t j = 0; j < m_height; ++j) {
        for (uint32_t i = 0; i < m_width; ++i) {
            m_matrix[i][j] = EMPTY_ROOM;
        }
    }
    m_rooms.clear();
}

uint32_t RoomMap::get_width() const
{
    return m_width;
}

uint32_t RoomMap::get_height() const
{
    return m_height;
}

const vector<Room>& RoomMap::get_rooms() const
{
    return m_rooms;
}

string RoomMap::to_string() const
{
    string str = "map( \n";
    for (const Room& room : m_rooms) {
        str += room.to_string() + '\n';
    }
    str += ")";
    return str;
}

int** RoomMap::get_matrix() const
{
    return m_matrix;
}

void RoomMap::initialize_matrix()
{
    m_matrix = new int*[m_width];
    for (uint32_t i = 0; i <= m_width; ++i) {
        m_matrix[i] = new int[m_height] {};
        std::fill_n(m_matrix[i], m_height, -1);
    }
}

void RoomMap::delete_matrix()
{
    for (uint32_t i = 0; i <= m_width; ++i) {
        delete[] m_matrix[i];
    }
    delete[] m_matrix;
}
