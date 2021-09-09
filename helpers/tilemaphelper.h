#pragma once

#include <cstdint>
#include <models/tilemap.h>

class TileMapHelper {
public:
    static TileMap create_tilemap();
    static int count_rooms( const TileMap& tilemap );
};