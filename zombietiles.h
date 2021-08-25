#pragma once

#include "tiletexture.h"
#include "zombietiles_global.h"
#include <list>

class ZOMBIETILES_EXPORT ZombieTiles
{
public:
    static std::list<TileTexture> generate_dungeon(const uint width, const uint height);
};
