#include "zombietiles.h"
#include "dungeonconfig.h"
#include "models/tilemap.h"
#include "utils/logger.h"
#include "utils/randomgenerator.h"
#include "zombietiles-ga/zombietilesga.h"

std::list<TileTexture> ZombieTiles::generate_dungeon(const uint32_t width, const uint32_t height)
{
    DungeonConfig dungeon_config = DungeonConfig::get_instance(width, height);

    ZombieTilesGA zombie_tiles_ga;

    zombie_tiles_ga.run();

    return {};
}
