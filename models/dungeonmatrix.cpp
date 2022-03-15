#include "dungeonmatrix.hpp"
#include <algorithm>

DungeonMatrix::DungeonMatrix(size_t width, size_t height)
    : m_width { width }
    , m_height { height }
    , m_max_index { 0 }
    , m_matrix { nullptr }
{
    m_matrix = new int*[m_width];
    for (uint32_t i = 0; i < m_width; ++i) {
        m_matrix[i] = new int[m_height] {};
        std::fill_n(m_matrix[i], m_height, -1);
    }
}

DungeonMatrix::~DungeonMatrix()
{
    for (uint32_t i = 0; i < m_width; ++i) {
        delete[] m_matrix[i];
    }
    delete[] m_matrix;
}

void swap(DungeonMatrix& first, DungeonMatrix& second)
{
    std::swap(first.m_height, second.m_height);
    std::swap(first.m_width, second.m_width);
    std::swap(first.m_matrix, second.m_matrix);
    std::swap(first.m_max_index, second.m_max_index);
}

DungeonMatrix::DungeonMatrix(const DungeonMatrix& other)
    : DungeonMatrix { other.width(), other.height() }
{
    set_max_index(other.m_max_index);
    for (uint32_t i = 0; i < m_width; ++i) {
        for (uint32_t j = 0; j < m_height; ++j) {
            m_matrix[i][j] = other[i][j];
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
    return m_matrix[index];
}

int& DungeonMatrix::operator[](const Point& point) const
{
    return m_matrix[point.x][point.y];
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
