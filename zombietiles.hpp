#pragma once

#include "zombietiles_global.hpp"
#include <cstdint>
#include <list>
#include <models/wall.hpp>

class RoomMap;

extern "C" RoomMap* generate_dungeon(const uint32_t width, const uint32_t height);

extern "C" void get_wall_array(RoomMap* dungeon, int& length, Wall*& array);

extern "C" void get_dungeon_matrix(RoomMap* dungeon, int& width, int& height, int**& array);

extern "C" void teste(RoomMap* dungeon, int& width, int& height, int**& array);
