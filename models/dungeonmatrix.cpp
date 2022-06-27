#include "dungeonmatrix.hpp"
#include <algorithm>

DungeonMatrix::DungeonMatrix(size_t width, size_t height)
    : m_width { width }
    , m_height { height }
    , m_max_index { 0 }
    , m_data { nullptr }
{
    m_data = new int*[m_width];
    for (uint32_t i = 0; i < m_width; ++i) {
        m_data[i] = new int[m_height] {};
        std::fill_n(m_data[i], m_height, -1);
    }
}

DungeonMatrix::~DungeonMatrix()
{
    for (uint32_t i = 0; i < m_width; ++i) {
        delete[] m_data[i];
    }
    delete[] m_data;
}

void swap(DungeonMatrix& first, DungeonMatrix& second)
{
    std::swap(first.m_height, second.m_height);
    std::swap(first.m_width, second.m_width);
    std::swap(first.m_data, second.m_data);
    std::swap(first.m_max_index, second.m_max_index);
    std::swap(first.m_allocated_rooms, second.m_allocated_rooms);
}

DungeonMatrix::DungeonMatrix(const DungeonMatrix& other)
    : DungeonMatrix { other.width(), other.height() }
{
    set_max_index(other.m_max_index);
    set_allocated_rooms(other.m_allocated_rooms);
    for (uint32_t i = 0; i < m_width; ++i) {
        for (uint32_t j = 0; j < m_height; ++j) {
            m_data[i][j] = other[i][j];
        }
    }
}

DungeonMatrix::DungeonMatrix(DungeonMatrix&& other) noexcept
    : DungeonMatrix(other.m_width, other.m_height)
{
    swap(*this, other);
}

DungeonMatrix& DungeonMatrix::operator=(DungeonMatrix other)
{
    swap(*this, other);
    return *this;
}

int* DungeonMatrix::operator[](const int index) const
{
    return m_data[index];
}

int& DungeonMatrix::operator[](const Point& point) const
{
    return m_data[point.x][point.y];
}

size_t DungeonMatrix::width() const
{
    return m_width;
}

size_t DungeonMatrix::height() const
{
    return m_height;
}

size_t DungeonMatrix::max_index() const
{
    return m_max_index;
}

void DungeonMatrix::set_max_index(size_t max_index)
{
    m_max_index = max_index;
}

int** DungeonMatrix::data() const
{
    return m_data;
}

const std::unordered_set<int>& DungeonMatrix::allocated_rooms()
{
    return m_allocated_rooms;
}

void DungeonMatrix::set_allocated_rooms(const std::unordered_set<int>& allocated_rooms)
{
    m_allocated_rooms = allocated_rooms;
}
