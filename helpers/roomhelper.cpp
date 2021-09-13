#include "roomhelper.h"
#include <utility>
#include <vector>

using namespace std;

bool RoomHelper::check_if_2_rooms_overlap(const Room& a, const Room& b)
{
    if ((b.get_placement_type() == Room::PlacementType::T
            && a.get_x() <= b.get_x()
            && a.get_x2() > b.get_x2()
            && a.get_y() <= b.get_y()
            && a.get_y2() > b.get_y2())
        || (b.get_placement_type() == Room::PlacementType::U
            && a.get_x() > b.get_x()
            && a.get_x2() <= b.get_x2()
            && a.get_y() > b.get_y()
            && a.get_y2() <= b.get_y2())) {
        return true;
    }

    vector<pair<const Room&, const Room&>> compare { { a, b }, { b, a } };

    for (pair<const Room&, const Room&> rooms : compare) {
        const Room& a = rooms.first;
        const Room& b = rooms.second;

        if (a.get_x() == b.get_x()) {
            if (a.get_x2() >= b.get_x2()
                && a.get_y() != b.get_y()
                && a.get_y2() < b.get_y2()) {
                return true;
            }

            if (a.get_x2() < b.get_x2()
                && a.get_y2() >= b.get_y2()) {
                return true;
            }
        }

        if (a.get_x() > b.get_x()) {
            if (a.get_x2() < b.get_x2()
                && a.get_y() < b.get_y()
                && a.get_y() >= b.get_y2()) {
                return true;
            }

            if (a.get_x2() >= b.get_x2()
                && a.get_x() < b.get_x2()) {
                return true;
            }
        }
    }

    return false;
}
