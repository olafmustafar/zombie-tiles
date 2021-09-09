#include "tilemaphelper.h"
#include "models/dungeonconfig.h"
#include <iostream>
#include <queue>
#include <utility>

TileMap TileMapHelper::create_tilemap()
{
    DungeonConfig dungeon_config = DungeonConfig::get_instance();
    TileMap tilemap(dungeon_config.get_width(), dungeon_config.get_height());
    return tilemap;
}

int TileMapHelper::count_rooms(const TileMap& tilemap)
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
