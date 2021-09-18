#pragma once

#include <cstdint>
#include <models/tilemap.hpp>
#include <vector>
#include <utility>

class TileMapHelper {
public:
    static void print_map( const TileMap& tilemap );
    static TileMap create_tilemap();
    static int count_rooms( const TileMap& tilemap );
    // static vector<pair<int, vector<int>>> generate_graph( const TileMap& tilemap );
};