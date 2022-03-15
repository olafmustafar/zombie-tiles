#include "roommaphelper.hpp"
#include "helpers/dungeonmatrixhelper.hpp"
#include "helpers/graphhelper.hpp"
#include "models/direction.hpp"
#include "models/dungeonconfig.hpp"
#include "models/graph.hpp"
#include "roomhelper.hpp"
#include "utils/randomgenerator.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <set>
#include <unordered_set>
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
        roommap.add_room(room);
        return;
    }

    vector<Room> rooms = roommap.get_rooms();
    auto new_room_overlaps = bind(&RoomHelper::check_if_overlaps, room, placeholders::_1);
    if (any_of(rooms.cbegin(), rooms.cend(), new_room_overlaps)) {
        return;
    }

    RoomMap copy(roommap);
    copy.add_room(room);
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

vector<Door> RoomMapHelper::generate_doors(const RoomMap& roommap)
{

    vector<bool> visited(roommap.get_rooms().size(), false);
    set<pair<int, int>> placed_doors {};
    vector<vector<vector<Door>>> doors_by_rooms {
        roommap.get_rooms().size(),
        vector<vector<Door>> {
            roommap.get_rooms().size(),
            vector<Door> {} }
    };

    for (uint32_t y = 0; y < roommap.get_height(); ++y) {
        for (uint32_t x = 0; x < roommap.get_width(); ++x) {
            int curr_room = roommap[x][y];
            if (curr_room == RoomMap::EMPTY_ROOM || visited[curr_room]) {
                continue;
            }

            Point origin { static_cast<int>(x), static_cast<int>(y) };
            Point curr { static_cast<int>(x), static_cast<int>(y) };

            Direction direction = Direction::UP;

            do {
                Point next = curr;

                switch (direction) {
                case Direction::UP:
                    --next.y;
                    break;
                case Direction::RIGHT:
                    ++next.x;
                    break;
                case Direction::LEFT:
                    --next.x;
                    break;
                case Direction::DOWN:
                    ++next.y;
                    break;
                }

                if (next.x < 0
                    || next.y < 0
                    || next.x == static_cast<int>(roommap.get_height())
                    || next.y == static_cast<int>(roommap.get_width())
                    || roommap[next] == RoomMap::EMPTY_ROOM
                    || (placed_doors.find(pair<int, int> { curr_room, roommap[next] }) != placed_doors.cend()
                        && visited[roommap[next]])) {
                    direction.turn_right();
                    continue;
                }

                if (roommap[next] == curr_room) {
                    curr = next;
                    direction.turn_left();

                } else {
                    switch (direction) {
                    case Direction::UP:
                        doors_by_rooms[curr_room][roommap[next]].emplace_back(curr, Door::horizontal);
                        break;
                    case Direction::RIGHT:
                        doors_by_rooms[curr_room][roommap[next]].emplace_back(next, Door::vertical);
                        break;
                    case Direction::LEFT:
                        doors_by_rooms[curr_room][roommap[next]].emplace_back(curr, Door::vertical);
                        break;
                    case Direction::DOWN:
                        doors_by_rooms[curr_room][roommap[next]].emplace_back(next, Door::horizontal);
                        break;
                    }
                    placed_doors.emplace(curr_room, roommap[next]);
                    placed_doors.emplace(roommap[next], curr_room);
                    direction.turn_right();
                }

            } while (direction != Direction::UP || curr != origin);

            visited[curr_room] = true;
        }
    }

    vector<Door> final_doors {};
    for (const vector<vector<Door>>& neighbors : doors_by_rooms) {
        for (const vector<Door>& door_locations : neighbors) {
            if (door_locations.empty()) {
                continue;
            }

            final_doors.push_back(door_locations[door_locations.size() / 2]);
        }
    }

    return final_doors;
}

vector<Wall> RoomMapHelper::walls_of(const RoomMap& roommap, const vector<Door>& doors)
{
    constexpr int EMPTY = -1;

    unordered_set<Door> door_set { doors.cbegin(), doors.cend() };

    vector<Wall> walls {};
    //Horizontal walls
    for (size_t y = 0; y <= roommap.get_height(); ++y) {
        int origin = EMPTY;
        for (size_t x = 0; x <= roommap.get_width(); ++x) {

            int above_cell = RoomMap::EMPTY_ROOM;
            int current_cell = RoomMap::EMPTY_ROOM;
            if (x != roommap.get_width()) {
                above_cell = y != 0 ? roommap[x][y - 1] : RoomMap::EMPTY_ROOM;
                current_cell = y != roommap.get_height() ? roommap[x][y] : RoomMap::EMPTY_ROOM;
            }

            if (above_cell != current_cell && origin == EMPTY && door_set.find({ { static_cast<int>(x), static_cast<int>(y) }, Door::horizontal }) == door_set.end()) {
                origin = x;
                continue;
            }

            if (origin != EMPTY
                && (above_cell == current_cell
                    || door_set.find({ { static_cast<int>(x), static_cast<int>(y) }, Door::horizontal }) != door_set.end())) {

                walls.push_back({
                    { static_cast<int>(origin), static_cast<int>(y) },
                    { static_cast<int>(x), static_cast<int>(y) },
                });
                origin = EMPTY;
            }
        }
    }

    //Vertical walls
    for (size_t x = 0; x <= roommap.get_width(); ++x) {
        int origin = EMPTY;
        for (size_t y = 0; y <= roommap.get_height(); ++y) {

            int left_cell = RoomMap::EMPTY_ROOM;
            int current_cell = RoomMap::EMPTY_ROOM;
            if (y != roommap.get_height()) {
                left_cell = x != 0 ? roommap[x - 1][y] : RoomMap::EMPTY_ROOM;
                current_cell = x != roommap.get_width() ? roommap[x][y] : RoomMap::EMPTY_ROOM;
            }

            if (left_cell != current_cell && origin == EMPTY && door_set.find({ { static_cast<int>(x), static_cast<int>(y) }, Door::vertical }) == door_set.end()) {
                origin = y;
                continue;
            }

            if (origin != EMPTY
                && (left_cell == current_cell
                    || door_set.find({ { static_cast<int>(x), static_cast<int>(y) }, Door::vertical }) != door_set.end())) {

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

DungeonMatrix RoomMapHelper::generate_dungeon_matrix(const RoomMap& roommap)
{
    DungeonMatrix matrix(roommap.width(), roommap.height());
    auto rooms = roommap.rooms();

    // placing tiles
    size_t room_count = 0;
    matrix.set_max_index(rooms.size() - 1);
    for (uint i = 0; i < rooms.size(); i++) {
        Room r = rooms[i];

        DungeonMatrix matrix_copy = matrix;

        for (uint32_t x = r.x; x < r.get_x2(); x++) {
            for (uint32_t y = r.y; y < r.get_y2(); y++) {
                int& current = matrix_copy[x][y];

                if (current == RoomMap::EMPTY_ROOM || r.get_placement_type() == Room::PlacementType::T) {
                    current = i;
                }
            }
        }

        if (DungeonMatrixHelper::rooms_count_of(matrix_copy) == (room_count + 1)) {
            matrix = std::move(matrix_copy);
            room_count++;
        }
    }

    Graph graph = to_graph(matrix);
    std::vector<std::vector<int>> distances = GraphHelper::distances_of(graph);
    std::set<int> unreachable_rooms {};

    // searching unreachable rooms
    for (size_t i = 0; i < distances.size(); i++) {
        if (std::all_of(distances[i].begin(), distances[i].end(), [](int d) { return d == -1; })) {
            unreachable_rooms.insert(i);
        }
    }

    // removing unreachable rooms
    for (size_t x = 0; x < matrix.width(); x++) {
        for (size_t y = 0; y < matrix.height(); y++) {
            int& current = matrix[x][y];
            if (unreachable_rooms.contains(current)) {
                current = RoomMap::EMPTY_ROOM;
            }
        }
    }

    return matrix;
}

void RoomMapHelper::add_player_to(RoomMap& dungeon)
{
    vector<vector<Point>> tiles_by_rooms(dungeon.get_rooms().size(), vector<Point> {});

    for (uint32_t y = 0; y < dungeon.get_height(); ++y) {
        for (uint32_t x = 0; x < dungeon.get_width(); ++x) {
            Point p { x, y };
            if (dungeon[p] != RoomMap::EMPTY_ROOM) {
                tiles_by_rooms[dungeon[p]].push_back(p);
            }
        }
    }

    vector<Point> player_room { Random::take_random_element(tiles_by_rooms) };
    dungeon.set_player({ EntityType::PLAYER, Random::random_element(player_room) });
}

void RoomMapHelper::generate_entities(RoomMap& roommap)
{
    const uint8_t enemies_per_room = 2;
    vector<bool> visited(roommap.get_rooms().size(), false);
    vector<vector<Point>> tiles_by_rooms(roommap.get_rooms().size(), vector<Point> {});

    // filling tiles_by_rooms
    for (uint32_t y = 0; y < roommap.get_height(); ++y) {
        for (uint32_t x = 0; x < roommap.get_width(); ++x) {
            Point p { x, y };
            if (roommap[p] != RoomMap::EMPTY_ROOM) {
                tiles_by_rooms[roommap[p]].push_back(p);
            }
        }
    }

    // placing player
    {
        vector<Point> player_room { Random::take_random_element(tiles_by_rooms) };
        roommap.set_player({ EntityType::PLAYER, Random::random_element(player_room) });
    }

    // placing enemies
    for (auto& tiles : tiles_by_rooms) {
        for (int i = 0; i < enemies_per_room; ++i) {
            if (tiles.empty()) {
                break;
            }

            Enemy e;
            e.position = Random::take_random_element(tiles);
            roommap.add_enemy(e);
        }
    }
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

Graph RoomMapHelper::to_graph(const DungeonMatrix& matrix)
{
    const size_t w = matrix.width();
    const size_t h = matrix.height();
    const size_t size = matrix.max_index() + 1;

    std::vector<std::vector<bool>> visited { w, std::vector<bool>(h, false) };

    Graph graph(size, std::vector<int>(size, -1));
    for (size_t i = 0; i < w; ++i) {
        for (size_t j = 0; j < h; ++j) {
            if (matrix[i][j] == RoomMap::EMPTY_ROOM || visited[i][j]) {
                continue;
            }

            int current_room = matrix[i][j];
            queue<pair<int, int>> to_visit {};
            to_visit.emplace(i, j);

            while (!to_visit.empty()) {
                pair<size_t, size_t> pos = to_visit.front();
                to_visit.pop();

                const auto x = pos.first;
                const auto y = pos.second;

                if (x < 0 || y < 0 || x >= w || y >= h
                    || matrix[x][y] == RoomMap::EMPTY_ROOM) {
                    continue;
                }

                graph[current_room][matrix[x][y]] = 1;

                if (matrix[x][y] == current_room
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

string RoomMapHelper::to_painted_map_string(const DungeonMatrix& matrix)
{

    const uint32_t w = matrix.width();
    const uint32_t h = matrix.height();

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

            if (matrix[i][j] == RoomMap::EMPTY_ROOM) {
                str += "   ";
            } else {
                str += "[" + std::to_string(matrix[i][j]) + "]";
            }

            if (i == w - 1) {
                str += "|";
            }
        }

        str += "\n";
    }
    return str;
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
