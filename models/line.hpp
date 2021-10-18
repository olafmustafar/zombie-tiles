#pragma once

#include "point.hpp"

struct Line {
    Line();
    Line(Point a, Point b);

    Point a;
    Point b;
};
