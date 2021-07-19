#include "zombietiles.h"
#include "dungeonconfig.h"
#include "tilemap.h"
#include "utils/logger.h"
#include "utils/randomgenerator.h"
#include "zombietiles-ga/zombietilesga.h"
#include <QDebug>

std::list<TileTexture> ZombieTiles::generate_dungeon(const u_int width, const u_int height)
{
    DungeonConfig dungeon_config(width, height);
    ZombieTilesGA zombie_tiles_ga(&dungeon_config);
    zombie_tiles_ga.run();

    Logger::doing("Testando");
    Logger::done();
    return {};
}
