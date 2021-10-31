#pragma once

#include "zombietiles_global.hpp"
#include <cstdint>
#include <list>
#include <models/door.hpp>
#include <models/wall.hpp>

class RoomMap;

extern "C" {

RoomMap* generate_dungeon(const uint32_t width, const uint32_t height);

void generate_wall_array(RoomMap* dungeon, int& size, Wall*& array);

void get_dungeon_matrix(RoomMap* dungeon, int& width, int& height, int**& array);

void generate_dungeon_doors(RoomMap* dungeon, int& size, Door*& array);

void free_dungeon(RoomMap* dungeon);

void free_wall_array(Wall* array);
}
