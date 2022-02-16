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

void generate_dungeon_rooms(RoomMap* dungeon, int& size, Room*& array);

void generate_dungeon_enemies(RoomMap* dungeon, int& size, Enemy*& array);

void generate_dungeon_player(RoomMap* dungeon, Entity*& player);

void generate_dungeon_walls(RoomMap* dungeon, int& size, Wall*& array);

void generate_dungeon_doors(RoomMap* dungeon, int& size, Door*& array);

void set_seed(int seed);

void free_dungeon(RoomMap* dungeon);

void free_wall_array(Wall* array);

void generate_dungeon_description(RoomMap* dungeon, int& size, char*& str);
}
