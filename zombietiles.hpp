#pragma once

#include "models/door.hpp"
#include "models/dungeon.hpp"
#include "models/dungeonmetadata.hpp"
#include "models/wall.hpp"
#include "zombietiles_global.hpp"
#include <cstdint>
#include <list>

extern "C" {

void set_population_size(size_t size);

void set_number_of_iterations(size_t number_of_iterations);

void set_number_of_iterations_without_change_limit(size_t number_of_iterations);

Dungeon* generate_dungeon(const uint32_t width, const uint32_t height);

Dungeon* generate_dungeon2(const uint32_t room_count, const uint32_t width, const uint32_t height);

Dungeon* load_dungeon(const char* path);

void save_dungeon(const Dungeon& dungeon, const char* path);

void get_dungeon_matrix(Dungeon* dungeon, int& width, int& height, int**& array);

void get_dungeon_distances_graph(Dungeon* dungeon, int& width, int& height, int**& array);

void generate_dungeon_rooms(Dungeon* dungeon, int& size, Room*& array);

void generate_dungeon_enemies(Dungeon* dungeon, int& size, Enemy*& array);

void generate_dungeon_enemies_v2(Dungeon* dungeon, int& size, Enemy*& array, size_t pool_size);

void generate_dungeon_player(Dungeon* dungeon, Entity*& player);

void generate_dungeon_walls(Dungeon* dungeon, int& size, Wall*& array);

void generate_dungeon_doors(Dungeon* dungeon, int& size, Door*& array);

void set_seed(int seed);

void free_dungeon(Dungeon* dungeon);

void free_wall_array(Wall* array);

void generate_dungeon_description(Dungeon* dungeon, int& size, char*& str);

DungeonMetadata generate_dungeon_metadata(Dungeon* dungeon);

int ping();
}
