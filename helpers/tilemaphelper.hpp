#pragma once

#include <cstdint>
#include <models/graph.hpp>
#include <models/tilemap.hpp>
#include <utility>
#include <vector>

class TileMapHelper {
public:
    static string to_painted_map_string(const TileMap& tilemap);
    static TileMap create_tilemap();
    static int rooms_count_of(const TileMap& tilemap);
    static Graph to_graph(const TileMap& tilemap);
};