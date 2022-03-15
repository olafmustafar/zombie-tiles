#include "dungeonmatrixhelper.hpp"
#include <cassert>
#include <models/point.hpp>
#include <queue>
#include <utility>
size_t DungeonMatrixHelper::narrow_rooms_of(const DungeonMatrix& dm)
{
    size_t count = 0;
    for (size_t y = 0; y < dm.width(); y++) {
        for (size_t x = 0; x < dm.height(); x++) {
            const int& current = dm[x][y];

            if (current == DungeonMatrix::EMPTY) {
                continue;
            }

            int upper = y == (dm.width() - 1) ? DungeonMatrix::EMPTY : dm[x][y + 1];
            int lower = y == 0 ? DungeonMatrix::EMPTY : dm[x][y - 1];
            int left = x == 0 ? DungeonMatrix::EMPTY : dm[x - 1][y];
            int right = x == (dm.height() - 1) ? DungeonMatrix::EMPTY : dm[x + 1][y];

            if ((current != upper && current != lower) ^ (current != left && current != right)) {
                count++;
            }
        }
    }
    return count;
}

size_t DungeonMatrixHelper::tiny_rooms_of(const DungeonMatrix& dm)
{
    size_t count = 0;
    for (size_t y = 0; y < dm.width(); y++) {
        for (size_t x = 0; x < dm.height(); x++) {
            const int& current = dm[x][y];

            if (current == DungeonMatrix::EMPTY) {
                continue;
            }

            if (current != (x == 0 ? DungeonMatrix::EMPTY : dm[x - 1][y])
                && current != (x == (dm.height() - 1) ? DungeonMatrix::EMPTY : dm[x + 1][y])
                && current != (y == 0 ? DungeonMatrix::EMPTY : dm[x][y - 1])
                && current != (y == (dm.width() - 1) ? DungeonMatrix::EMPTY : dm[x][y + 1])) {
                count++;
            }
        }
    }
    return count;
}

size_t DungeonMatrixHelper::rooms_count_of(const DungeonMatrix& dm)
{
    const size_t w = dm.width();
    const size_t h = dm.height();

    using namespace std;

    vector<vector<bool>> visited(w, vector<bool>(h, false));

    size_t count = 0;

    for (size_t x = 0; x < w; ++x) {
        for (size_t y = 0; y < h; ++y) {
            if (dm[x][y] == DungeonMatrix::EMPTY || visited[x][y]) {
                continue;
            }

            queue<Point> to_visit {};
            to_visit.emplace(static_cast<int>(x), static_cast<int>(y));
            const int& current = dm[x][y];

            while (!to_visit.empty()) {
                Point pos = to_visit.front();
                to_visit.pop();

                if (pos.x < 0
                    || pos.y < 0
                    || static_cast<size_t>(pos.x) == w
                    || static_cast<size_t>(pos.y) == h
                    || visited[pos.x][pos.y]) {
                    continue;
                }

                if (current == dm[pos.x][pos.y]) {
                    visited[pos.x][pos.y] = true;
                    to_visit.emplace(pos.x + 1, pos.y);
                    to_visit.emplace(pos.x - 1, pos.y);
                    to_visit.emplace(pos.x, pos.y + 1);
                    to_visit.emplace(pos.x, pos.y - 1);
                }
            }
            count++;
        }
    }

    return count;
}
