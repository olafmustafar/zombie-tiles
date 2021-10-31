#pragma once

#include <functional>

struct Point {
    Point();
    Point(int x, int y);

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;

    int x;
    int y;
};

template <>
struct std::hash<Point> {
    std::size_t operator()(const Point& p) const noexcept
    {
        std::size_t h1 = std::hash<int> {}(p.x);
        std::size_t h2 = std::hash<int> {}(p.y);
        return h1 ^ (h2 << 1);
    }
};
