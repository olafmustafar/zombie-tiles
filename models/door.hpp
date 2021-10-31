#pragma once

#include "point.hpp"

struct Door {
    enum Orientation {
        horizontal,
        vertical,
    };
    Door();
    Door(const Point& location, Orientation orientation);

    Point location;
    Orientation orientation;
};
