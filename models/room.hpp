#pragma once

#include <string>
using namespace std;

class Room {
public:
    enum PlacementType : int {
        T, // Top
        U, // Under
    };

    Room();
    Room(uint32_t x, uint32_t y, uint32_t width, uint32_t height, PlacementType placement_type);

    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
    PlacementType placement_type;

    uint32_t get_x() const;
    void set_x(uint32_t value);

    uint32_t get_y() const;
    void set_y(uint32_t value);

    uint32_t get_width() const;
    void set_width(uint32_t value);

    uint32_t get_height() const;
    void set_height(uint32_t value);

    uint32_t get_x2() const;
    uint32_t get_y2() const;

    PlacementType get_placement_type() const;
    void set_placement_type(const PlacementType& value);

    void print() const;
    string to_string() const;
};
