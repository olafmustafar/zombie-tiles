#pragma once

#include <cstdint>
#include <models/door.hpp>
#include <models/graph.hpp>
#include <models/roommap.hpp>
#include <models/wall.hpp>
#include <utility>
#include <vector>

class RoomMapHelper {
public:
    static RoomMap create_roommap();
    static void add_room_to(RoomMap& tilemap, const Room& room);
    static size_t rooms_count_of(const RoomMap& roommap);
    static int narrow_rooms_of(const RoomMap& roommap);
    static int tiny_rooms_of(const RoomMap& roommap);
    static vector<Door> generate_doors(const RoomMap& roommap);
    static vector<Wall> walls_of(const RoomMap& roommap, const vector<Door>& doors);
    static void generate_enemies(RoomMap& roommap);

    static string to_painted_map_string(const RoomMap& roommap);
    static Graph to_graph(const RoomMap& roommap);
};
