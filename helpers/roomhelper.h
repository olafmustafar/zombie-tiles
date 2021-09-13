#pragma once

#include <models/room.h>

class RoomHelper {
public:
    static bool check_if_2_rooms_overlap(const Room& a, const Room& b);
};