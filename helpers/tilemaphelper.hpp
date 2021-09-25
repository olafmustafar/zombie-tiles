#pragma once

#include <cstdint>
#include <models/graph.hpp>
#include <models/tilemap.hpp>
#include <utility>
#include <vector>

class TileMapHelper {
public:
    static TileMap create_tilemap();
    static void add_room_to(TileMap& tilemap, const Room& room);
    static int rooms_count_of(const TileMap& tilemap);
    static int narrow_rooms_of(const TileMap& tilemap);
    static int tiny_rooms_of(const TileMap& tilemap);
    static string to_painted_map_string(const TileMap& tilemap);
    static Graph to_graph(const TileMap& tilemap);
};