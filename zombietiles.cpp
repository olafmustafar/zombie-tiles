#include "zombietiles.h"
#include "dungeonconfig.h"
#include "tilemap.h"
#include "utils/logger.h"
#include "utils/randomgenerator.h"
#include "zombietiles-ga/zombietilesga.h"

std::list<TileTexture> ZombieTiles::generate_dungeon(const uint width, const uint height)
{
    DungeonConfig dungeon_config = DungeonConfig::get_instance(width, height);

    ZombieTilesGA zombie_tiles_ga;

    zombie_tiles_ga.run();

    return {};
}
