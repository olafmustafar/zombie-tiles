#pragma once

#include "models/enemiesconfig.hpp"
#include <cstdint>
#include <models/door.hpp>
#include <models/dungeon.hpp>
#include <models/dungeonmatrix.hpp>
#include <models/dungeonmetadata.hpp>
#include <models/enemiesmetadata.hpp>
#include <models/graph.hpp>
#include <models/wall.hpp>
#include <utility>
#include <vector>

class RoomMapHelper {
public:
    static Dungeon create_roommap();

    static DungeonMetadata calculate_dungeon_metadata(Dungeon& dungeon);
    static EnemiesMetadata calculate_enemiegenes_metadata(const EnemiesConfig enemies_config, const std::vector<Enemy>& enemies);

    static void add_room_to(Dungeon& tilemap, const Room& room);
    static void add_player_to(Dungeon& dungeon);

    static size_t rooms_count_of(const Dungeon& roommap);
    static int narrow_rooms_of(const Dungeon& roommap);
    static int tiny_rooms_of(const Dungeon& roommap);
    static vector<Wall> walls_of(Dungeon& roommap, const vector<Door>& doors);

    static DungeonMatrix generate_dungeon_matrix(const Dungeon& roommap);
    static vector<Door> generate_doors(Dungeon& roommap);

    [[deprecated("Substituido pela ga")]] static void generate_entities(Dungeon& roommap);

    static string to_painted_map_string(const Dungeon& roommap);
    static string to_painted_map_string(const DungeonMatrix& matrix);
    static Graph to_graph(const Dungeon& roommap);
    static Graph to_graph(const DungeonMatrix& matrix);
};
