#include "roommaphelper.hpp"
#include "models/dungeonconfig.hpp"
#include "roomhelper.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>

using namespace std;

RoomMap RoomMapHelper::create_tilemap()
{
    DungeonConfig dungeon_config = DungeonConfig::get_instance();
    RoomMap tilemap(dungeon_config.get_width(), dungeon_config.get_height());
    return tilemap;
}

void RoomMapHelper::add_room_to(RoomMap& tilemap, const Room& room)
{
    int original_size = tilemap.get_rooms().size();

    if (original_size == 0) {
        tilemap.addRoom(room);
        return;
    }

    vector<Room> rooms = tilemap.get_rooms();
    auto new_room_overlaps = bind(&RoomHelper::check_if_overlaps, room, placeholders::_1);
    if (!any_of(rooms.cbegin(), rooms.cend(), new_room_overlaps)) {
        return;
    }

    RoomMap copy(tilemap);
    copy.addRoom(room);
    if (rooms_count_of(copy) == original_size + 1) {
        tilemap = std::move(copy);
    }
}

size_t RoomMapHelper::rooms_count_of(const RoomMap& tilemap)
{
    const uint32_t w = tilemap.get_width();
    const uint32_t h = tilemap.get_height();

    int visited[w][h] {};

    size_t room_index = 1;

    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            if (tilemap[i][j] == RoomMap::EMPTY_ROOM || visited[i][j] != 0) {
                continue;
            }

            queue<pair<int, int>> to_visit {};
            to_visit.emplace(i, j);
            int current_room = tilemap[i][j];

            while (!to_visit.empty()) {
                pair<int, int> pos = to_visit.front();
                to_visit.pop();

                if (pos.first < 0 || pos.second < 0 || pos.first >= w || pos.second >= h) {
                    continue;
                }

                if (tilemap[pos.first][pos.second] == current_room
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

int RoomMapHelper::narrow_rooms_of(const RoomMap& tilemap)
{
    int narrow_rooms_count = 0;
    for (const Room& room : tilemap.get_rooms()) {
        if ((room.get_width() == 1 && room.get_height() != 1)
            || (room.get_width() != 1 && room.get_height() == 1)) {
            ++narrow_rooms_count;
        }
    }
    return narrow_rooms_count;
}

int RoomMapHelper::tiny_rooms_of(const RoomMap& tilemap)
{
    int tiny_rooms_count = 0;
    vector<bool> counted(tilemap.get_rooms().size(), false);

    for (uint32_t x = 0; x < tilemap.get_width(); ++x) {
        for (uint32_t y = 0; y < tilemap.get_height(); ++y) {
            int current_room = tilemap[x][y];
            if (current_room == RoomMap::EMPTY_ROOM || counted[current_room]) {
                continue;
            };

            if (x > 0) {
                if (tilemap[x - 1][y] == current_room) {
                    counted[current_room] = true;
                    continue;
                }
            }

            if (y > 0) {
                if (tilemap[x][y - 1] == current_room) {
                    counted[current_room] = true;
                    continue;
                }
            }

            if (x < tilemap.get_width() - 1) {
                if (tilemap[x + 1][y] == current_room) {
                    counted[current_room] = true;
                    continue;
                }
            }

            if (y < tilemap.get_width() - 1) {
                if (tilemap[x][y + 1] == current_room) {
                    counted[current_room] = true;
                    continue;
                }
            }

            ++tiny_rooms_count;
        }
    }
    return tiny_rooms_count;
}

Graph RoomMapHelper::to_graph(const RoomMap& tilemap)
{
    const int w = tilemap.get_width();
    const int h = tilemap.get_height();
    const size_t size = tilemap.get_rooms().size();

    bool visited[w][h] {};

    Graph graph(size, vector<int>(size, -1));

    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            if (tilemap[i][j] == RoomMap::EMPTY_ROOM || visited[i][j]) {
                continue;
            }

            int current_room = tilemap[i][j];
            queue<pair<int, int>> to_visit {};
            to_visit.emplace(i, j);

            while (!to_visit.empty()) {
                pair<int, int> pos = to_visit.front();
                to_visit.pop();

                const int x = pos.first;
                const int y = pos.second;

                if (x < 0 || y < 0 || x >= w || y >= h
                    || tilemap[x][y] == RoomMap::EMPTY_ROOM) {
                    continue;
                }

                graph[current_room][tilemap[x][y]] = 1;

                if (tilemap[x][y] == current_room
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

string RoomMapHelper::to_painted_map_string(const RoomMap& tilemap)
{
    const uint32_t w = tilemap.get_width();
    const uint32_t h = tilemap.get_height();

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

            if (tilemap[i][j] == RoomMap::EMPTY_ROOM) {
                str += "   ";
            } else {
                str += "[" + std::to_string(tilemap[i][j]) + "]";
            }

            if (i == w - 1) {
                str += "|";
            }
        }

        str += "\n";
    }
    return str;
}
