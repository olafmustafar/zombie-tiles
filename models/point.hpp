#pragma once

struct Point {
    Point();
    Point(int x, int y);

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;

    int x;
    int y;
};
