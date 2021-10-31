#pragma once

#include "point.hpp"
#include <functional>

struct Door {
    enum Orientation {
        horizontal,
        vertical,
    };
    Door();
    Door(const Point& location, Orientation orientation);
    bool operator==(const Door& other) const;

    Point location;
    Orientation orientation;
};

template <>
struct std::hash<Door> {
    std::size_t operator()(const Door& d) const noexcept
    {
        std::size_t h1 = std::hash<Point> {}(d.location);
        std::size_t h2 = std::hash<int> {}(d.orientation);
        return h1 ^ h2;
    }
};
