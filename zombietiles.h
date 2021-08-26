#pragma once

#include "tiletexture.h"
#include "zombietiles_global.h"
#include <list>
#include <cstdint>

class ZOMBIETILES_EXPORT ZombieTiles
{
public:
    static std::list<TileTexture> generate_dungeon(const uint32_t width, const uint32_t height);
};
