#pragma once

#include "zombietiles_global.hpp"
#include <cstdint>
#include <list>
#include <models/door.hpp>
#include <models/roommap.hpp>
#include <models/wall.hpp>

extern "C" {

RoomMap* generate_dungeon(const uint32_t width, const uint32_t height);

void get_dungeon_matrix(RoomMap* dungeon, int& width, int& height, int**& array);

void generate_dungeon_entities(RoomMap* dungeon, int& size, Entity*& array);

void generate_wall_array(RoomMap* dungeon, int& size, Wall*& array);

void generate_dungeon_doors(RoomMap* dungeon, int& size, Door*& array);

void set_seed(int seed);

void free_dungeon(RoomMap* dungeon);

void free_wall_array(Wall* array);
}
