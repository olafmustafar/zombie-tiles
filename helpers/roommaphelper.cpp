#include "roommaphelper.hpp"
#include "models/dungeonconfig.hpp"
#include "roomhelper.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>

using namespace std;

RoomMap RoomMapHelper::create_roommap()
{
    DungeonConfig dungeon_config = DungeonConfig::get_instance();
    RoomMap roommap(dungeon_config.get_width(), dungeon_config.get_height());
    return roommap;
}

void RoomMapHelper::add_room_to(RoomMap& roommap, const Room& room)
{
    int original_size = roommap.get_rooms().size();

    if (original_size == 0) {
        roommap.addRoom(room);
        return;
    }

    vector<Room> rooms = roommap.get_rooms();
    auto new_room_overlaps = bind(&RoomHelper::check_if_overlaps, room, placeholders::_1);
    if (!any_of(rooms.cbegin(), rooms.cend(), new_room_overlaps)) {
        return;
    }

    RoomMap copy(roommap);
    copy.addRoom(room);
    if (rooms_count_of(copy) == original_size + 1) {
        roommap = std::move(copy);
    }
}

size_t RoomMapHelper::rooms_count_of(const RoomMap& roommap)
{
    const uint32_t w = roommap.get_width();
    const uint32_t h = roommap.get_height();

    int visited[w][h] {};

    size_t room_index = 1;

    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            if (roommap[i][j] == RoomMap::EMPTY_ROOM || visited[i][j] != 0) {
                continue;
            }

            queue<pair<int, int>> to_visit {};
            to_visit.emplace(i, j);
            int current_room = roommap[i][j];

            while (!to_visit.empty()) {
                pair<int, int> pos = to_visit.front();
                to_visit.pop();

                if (pos.first < 0 || pos.second < 0 || pos.first >= w || pos.second >= h) {
                    continue;
                }

                if (roommap[pos.first][pos.second] == current_room
                    && visited[pos.first][pos.second] != room_index) {

                    visited[pos.first][pos.second] = room_index;
                    to_visit.emplace(pos.first + 1, pos.second);
                    to_visit.emplace(pos.first - 1, pos.second);
                    to_visit.emplace(pos.first, pos.second + 1);
                    to_visit.emplace(pos.first, pos.second - 1);
                }
            }
            ++room_index;
        }
    }

    return room_index - 1;
}

int RoomMapHelper::narrow_rooms_of(const RoomMap& roommap)
{
    int narrow_rooms_count = 0;
    for (const Room& room : roommap.get_rooms()) {
        if ((room.get_width() == 1 && room.get_height() != 1)
            || (room.get_width() != 1 && room.get_height() == 1)) {
            ++narrow_rooms_count;
        }
    }
    return narrow_rooms_count;
}

int RoomMapHelper::tiny_rooms_of(const RoomMap& roommap)
{
    int tiny_rooms_count = 0;
    vector<bool> counted(roommap.get_rooms().size(), false);

    for (uint32_t x = 0; x < roommap.get_width(); ++x) {
        for (uint32_t y = 0; y < roommap.get_height(); ++y) {
            int current_room = roommap[x][y];
            if (current_room == RoomMap::EMPTY_ROOM || counted[current_room]) {
                continue;
            };

            if (x > 0) {
                if (roommap[x - 1][y] == current_room) {
                    counted[current_room] = true;
                    continue;
                }
            }

            if (y > 0) {
                if (roommap[x][y - 1] == current_room) {
                    counted[current_room] = true;
                    continue;
                }
            }

            if (x < roommap.get_width() - 1) {
                if (roommap[x + 1][y] == current_room) {
                    counted[current_room] = true;
                    continue;
                }
            }

            if (y < roommap.get_width() - 1) {
                if (roommap[x][y + 1] == current_room) {
                    counted[current_room] = true;
                    continue;
                }
            }

            ++tiny_rooms_count;
        }
    }
    return tiny_rooms_count;
}

vector<Wall> RoomMapHelper::walls_of(const RoomMap& roommap)
{
    constexpr int EMPTY = -1;
    vector<Wall> walls {};

    for (size_t y = 0; y <= roommap.get_height(); ++y) {
        int origin = EMPTY;
        for (size_t x = 0; x <= roommap.get_width(); ++x) {

            int above_cell = y != 0 ? roommap[x][y - 1] : RoomMap::EMPTY_ROOM;
            int current_cell = y != roommap.get_height() ? roommap[x][y] : RoomMap::EMPTY_ROOM;

            if (above_cell != current_cell && origin == EMPTY) {
                origin = x;
                continue;
            }

            if ((above_cell == current_cell || x == roommap.get_width()) && origin != EMPTY) {
                walls.push_back({
                    { static_cast<int>(origin), static_cast<int>(y) },
                    { static_cast<int>(x), static_cast<int>(y) },
                });
                origin = EMPTY;
            }
        }
    }

    for (size_t x = 0; x <= roommap.get_width(); ++x) {
        int origin = EMPTY;
        for (size_t y = 0; y <= roommap.get_height(); ++y) {

            int left_cell = x != 0 ? roommap[x - 1][y] : RoomMap::EMPTY_ROOM;
            int current_cell = x != roommap.get_width() ? roommap[x][y] : RoomMap::EMPTY_ROOM;

            if (left_cell != current_cell && origin == EMPTY) {
                origin = y;
                continue;
            }

            if ((left_cell == current_cell || y == roommap.get_height()) && origin != EMPTY) {
                walls.push_back({
                    { static_cast<int>(x), static_cast<int>(origin) },
                    { static_cast<int>(x), static_cast<int>(y) },
                });
                origin = EMPTY;
            }
        }
    }

    return walls;
}

Graph RoomMapHelper::to_graph(const RoomMap& roommap)
{
    const int w = roommap.get_width();
    const int h = roommap.get_height();
    const size_t size = roommap.get_rooms().size();

    bool visited[w][h] {};

    Graph graph(size, vector<int>(size, -1));

    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            if (roommap[i][j] == RoomMap::EMPTY_ROOM || visited[i][j]) {
                continue;
            }

            int current_room = roommap[i][j];
            queue<pair<int, int>> to_visit {};
            to_visit.emplace(i, j);

            while (!to_visit.empty()) {
                pair<int, int> pos = to_visit.front();
                to_visit.pop();

                const int x = pos.first;
                const int y = pos.second;

                if (x < 0 || y < 0 || x >= w || y >= h
                    || roommap[x][y] == RoomMap::EMPTY_ROOM) {
                    continue;
                }

                graph[current_room][roommap[x][y]] = 1;

                if (roommap[x][y] == current_room
                    && !visited[x][y]) {

                    visited[x][y] = true;
                    to_visit.emplace(x + 1, y);
                    to_visit.emplace(x - 1, y);
                    to_visit.emplace(x, y + 1);
                    to_visit.emplace(x, y - 1);
                }
            }
        }
    }
    return graph;
}

string RoomMapHelper::to_painted_map_string(const RoomMap& roommap)
{
    const uint32_t w = roommap.get_width();
    const uint32_t h = roommap.get_height();

    string str = "\n     ";
    {
        string linha = "     ";
        for (uint32_t i = 0; i < w; ++i) {
            char buffer[255];
            sprintf(buffer, "%3d", i);
            str += buffer;
            linha += "___";
        }
        str += "\n" + linha + "\n";
    }

    for (uint32_t j = 0; j < h; ++j) {
        for (uint32_t i = 0; i < w; ++i) {
            if (i == 0) {
                char buffer[255];
                sprintf(buffer, "% 3d |", j);
                str += buffer;
            }

            if (roommap[i][j] == RoomMap::EMPTY_ROOM) {
                str += "   ";
            } else {
                str += "[" + std::to_string(roommap[i][j]) + "]";
            }

            if (i == w - 1) {
                str += "|";
            }
        }

        str += "\n";
    }
    return str;
}
