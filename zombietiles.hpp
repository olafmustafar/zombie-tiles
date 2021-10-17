#pragma once

#include "zombietiles_global.hpp"
#include <cstdint>
#include <list>

extern "C" void generate_dungeon(const uint32_t width, const uint32_t height);

extern "C" void get_corridors();

extern "C" int teste();
