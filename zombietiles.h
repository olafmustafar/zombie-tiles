#pragma once

#include "tile.h"
#include "tiletexture.h"
#include "zombietiles_global.h"
#include <list>

class ZOMBIETILES_EXPORT ZombieTiles
{
public:
    static std::list<TileTexture> generate_dungeon(const u_int width, const u_int height);
};
