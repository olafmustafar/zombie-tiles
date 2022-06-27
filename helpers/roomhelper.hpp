#pragma once

#include <models/point.hpp>
#include <models/room.hpp>
#include <vector>

using namespace std;

class RoomHelper {
public:
    static bool check_if_can_add(const Room& new_room, const vector<Room>& rooms);
    static bool check_if_overlaps(const Room& room, const Room& another);
    static bool check_if_room_collides(const Room& room, const Room& another);
    static bool check_if_hides_or_is_hidden(const Room& room, const Room& another);
    static bool check_if_divides_room(const Room& room, const Room& another);
    static double distance(const Room& room, const Room& another);

private:
    static bool check_if_point_collides(const Room& room, const Point& p);
};
