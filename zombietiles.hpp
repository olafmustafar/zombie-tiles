#pragma once

#include "zombietiles_global.hpp"
#include <cstdint>
#include <list>
#include <models/door.hpp>
#include <models/dungeon.hpp>
#include <models/wall.hpp>

extern "C" {

Dungeon* generate_dungeon(const uint32_t width, const uint32_t height);

Dungeon* load_dungeon(const char* path);

void save_dungeon(const Dungeon& dungeon, const char* path);

void get_dungeon_matrix(Dungeon* dungeon, int& width, int& height, int**& array);

void get_dungeon_distances_graph(Dungeon* dungeon, int& width, int& height, int**& array);

void generate_dungeon_rooms(Dungeon* dungeon, int& size, Room*& array);

void generate_dungeon_enemies(Dungeon* dungeon, int& size, Enemy*& array);

void generate_dungeon_player(Dungeon* dungeon, Entity*& player);

void generate_dungeon_walls(Dungeon* dungeon, int& size, Wall*& array);

void generate_dungeon_doors(Dungeon* dungeon, int& size, Door*& array);

void set_seed(int seed);

void free_dungeon(Dungeon* dungeon);

void free_wall_array(Wall* array);

void generate_dungeon_description(Dungeon* dungeon, int& size, char*& str);
}
