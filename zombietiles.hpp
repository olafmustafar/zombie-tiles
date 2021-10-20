#pragma once

#include "zombietiles_global.hpp"
#include <cstdint>
#include <list>
#include <models/wall.hpp>

extern "C" void generate_dungeon(const uint32_t width, const uint32_t height);

extern "C" void get_wall_array(int& length, Wall*& array);

extern "C" void teste(int& length, Wall*& array);
