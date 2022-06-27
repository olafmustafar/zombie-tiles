#pragma once

#include "point.hpp"
#include <cstdint>
#include <unordered_set>

struct DungeonMatrix {
public:
    static constexpr int EMPTY = -1;

    DungeonMatrix(size_t width, size_t height);
    ~DungeonMatrix();
    friend void swap(DungeonMatrix& first, DungeonMatrix& second);
    DungeonMatrix(const DungeonMatrix& other);
    DungeonMatrix(DungeonMatrix&& other) noexcept;

    DungeonMatrix& operator=(DungeonMatrix other);

    int* operator[](const int index) const;
    int& operator[](const Point& point) const;

    size_t width() const;
    size_t height() const;

    size_t max_index() const;
    void set_max_index(size_t max_index);

    const std::unordered_set<int>& allocated_rooms();
    void set_allocated_rooms(const std::unordered_set<int>& allocated_rooms);

    int** data() const;

private:
    size_t m_width;
    size_t m_height;
    size_t m_max_index;
    std::unordered_set<int> m_allocated_rooms;
    int** m_data;

};
