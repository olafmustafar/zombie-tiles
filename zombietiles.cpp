#include "zombietiles.h"
#include "tilemap.h"

std::list<TileTexture> ZombieTiles::generate_dungeon(const u_int width, const u_int height)
{
    TileMap *tileMap = new TileMap(width, height);
    tileMap->init();
    //    tileMap-> get_tile({2, 5})->type();
    tileMap->print();
    return {};
}
