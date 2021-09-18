#pragma once

#include "zombietiles_global.hpp"
#include <list>
#include <cstdint>

class ZOMBIETILES_EXPORT ZombieTiles
{
public:
    static void generate_dungeon(const uint32_t width, const uint32_t height);
};
