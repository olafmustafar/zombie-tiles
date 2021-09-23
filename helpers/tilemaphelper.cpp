#include "tilemaphelper.hpp"
#include "models/dungeonconfig.hpp"
#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>

using namespace std;

string TileMapHelper::to_painted_map_string(const TileMap& tilemap)
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

            if (tilemap[i][j] == TileMap::EMPTY_ROOM) {
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

TileMap TileMapHelper::create_tilemap()
{
    DungeonConfig dungeon_config = DungeonConfig::get_instance();
    TileMap tilemap(dungeon_config.get_width(), dungeon_config.get_height());
    return tilemap;
}

int TileMapHelper::rooms_count_of(const TileMap& tilemap)
{
    const int w = tilemap.get_width();
    const int h = tilemap.get_height();

    int visited[w][h] {};

    int room_index = 1;

    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            if (tilemap[i][j] == TileMap::EMPTY_ROOM || visited[i][j] != 0) {
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

Graph TileMapHelper::to_graph(const TileMap& tilemap)
{
    const int w = tilemap.get_width();
    const int h = tilemap.get_height();
    const size_t size = tilemap.get_rooms().size();

    bool visited[w][h] {};

    Graph graph(size, vector<int>(size, -1));

    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            if (tilemap[i][j] == TileMap::EMPTY_ROOM || visited[i][j]) {
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
                    || tilemap[x][y] == TileMap::EMPTY_ROOM) {
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
