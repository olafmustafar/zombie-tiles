#pragma once

#include <cstdint>
#include <models/tilemap.hpp>
#include <vector>
#include <utility>

class TileMapHelper {
public:
    static string to_painted_map_string( const TileMap& tilemap );
    static TileMap create_tilemap();
    static int count_rooms( const TileMap& tilemap );
    // static vector<pair<int, vector<int>>> generate_graph( const TileMap& tilemap );
};