#pragma once

#include <cstdint>
#include <models/graph.hpp>
#include <models/roommap.hpp>
#include <utility>
#include <vector>

class RoomMapHelper {
public:
    static RoomMap create_roommap();
    static void add_room_to(RoomMap& tilemap, const Room& room);
    static size_t rooms_count_of(const RoomMap& tilemap);
    static int narrow_rooms_of(const RoomMap& tilemap);
    static int tiny_rooms_of(const RoomMap& tilemap);
    static string to_painted_map_string(const RoomMap& tilemap);
    static Graph to_graph(const RoomMap& tilemap);
};
