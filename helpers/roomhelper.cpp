#include "roomhelper.hpp"
#include <algorithm>
#include <functional>
#include <utility>
#include <utils/logger.hpp>
#include <vector>
using namespace std;

bool RoomHelper::check_if_can_add(const Room& new_room, const vector<Room>& rooms)
{
    if (!rooms.size()) {
        return true;
    }

    auto new_room_overlaps = bind(&check_if_overlaps, new_room, placeholders::_1);
    if (!any_of(rooms.cbegin(), rooms.cend(), new_room_overlaps)) {
        return false;
    }

    auto new_room_hides = bind(&check_if_hides_or_is_hidden, new_room, placeholders::_1);
    if (any_of(rooms.cbegin(), rooms.cend(), new_room_hides)) {
        return false;
    };

    auto new_room_divides = bind(&check_if_divides_room, new_room, placeholders::_1);
    if (any_of(rooms.cbegin(), rooms.cend(), new_room_divides)) {
        return false;
    }

    return true;
}

bool RoomHelper::check_if_overlaps(const Room& room, const Room& another)
{
    vector<pair<const Room&, const Room&>> compare { { room, another }, { another, room } };

    for (pair<const Room&, const Room&> rooms : compare) {

        const Room& a = rooms.first;
        const Room& b = rooms.second;
        vector<pair<int, int>> edges({
            { a.get_x(), a.get_y() },
            { a.get_x2(), a.get_y() },
            { a.get_x(), a.get_y2() },
            { a.get_x2(), a.get_y2() },
        });

        for (pair<int, int> edge : edges) {
            const int x = edge.first;
            const int y = edge.second;

            if (x >= b.get_x()
                && x <= b.get_x2()
                && y >= b.get_y()
                && y <= b.get_y2()) {
                return true;
            }
        }
    }

    return false;
}

bool RoomHelper::check_if_hides_or_is_hidden(const Room& room, const Room& another)
{
    return (
        (room.get_placement_type() == Room::PlacementType::T
            && room.get_x() <= another.get_x()
            && room.get_y() <= another.get_y()
            && room.get_x2() >= another.get_x2()
            && room.get_y2() >= another.get_y2())
        || (room.get_placement_type() == Room::PlacementType::U
            && room.get_x() >= another.get_x()
            && room.get_y() >= another.get_y()
            && room.get_x2() <= another.get_x2()
            && room.get_y2() <= another.get_y2()));
}

bool RoomHelper::check_if_divides_room(const Room& room, const Room& another)
{
    if (room.get_width() >= another.get_width()) {
        if ((room.get_placement_type() == Room::PlacementType::T
                && room.get_x() <= another.get_x()
                && room.get_x2() >= another.get_x2())
            || (room.get_placement_type() == Room::PlacementType::U
                && room.get_x() < another.get_x()
                && room.get_x2() > another.get_x2())) {

            if (room.get_y() >= another.get_y()
                && room.get_y() < another.get_y2()) {
                return true;
            }

            if (room.get_y2() > another.get_y()
                && room.get_y2() <= another.get_y2()) {
                return true;
            }
        }
    }

    if (room.get_height() >= another.get_height()) {
        if ((room.get_placement_type() == Room::PlacementType::T
                && room.get_y() <= another.get_y()
                && room.get_y2() >= another.get_y2())
            || (room.get_placement_type() == Room::PlacementType::U
                && room.get_y() < another.get_y()
                && room.get_y2() > another.get_y2())) {

            if (room.get_x() >= another.get_x()
                && room.get_x() < another.get_x2()) {
                return true;
            }

            if (room.get_x2() > another.get_x()
                && room.get_x2() <= another.get_x2()) {
                return true;
            }
        }
    }

    return false;
}
