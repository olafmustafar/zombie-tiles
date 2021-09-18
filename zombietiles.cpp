#include "zombietiles.hpp"
#include "models/dungeonconfig.hpp"
#include "models/tilemap.hpp"
#include "utils/logger.hpp"
#include "utils/randomgenerator.hpp"
#include "zombietiles-ga/zombietilesga.hpp"

void ZombieTiles::generate_dungeon(const uint32_t width, const uint32_t height)
{
    DungeonConfig dungeon_config = DungeonConfig::get_instance(width, height);

    ZombieTilesGA ga;

    ga.run();

    return;
}
