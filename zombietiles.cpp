#include "zombietiles.hpp"
#include "models/dungeonconfig.hpp"
#include "models/roommap.hpp"
#include "utils/logger.hpp"
#include "utils/randomgenerator.hpp"
#include "zombietiles-ga/zombietilesga.hpp"

#include <helpers/roommaphelper.hpp>

namespace {
RoomMap* dungeon = nullptr;
}

void generate_dungeon(const uint32_t width, const uint32_t height)
{
    DungeonConfig& dungeon_config = DungeonConfig::get_instance();
    dungeon_config.set_width(width);
    dungeon_config.set_height(height);
    dungeon_config.set_rooms_count(10); // 10
    dungeon_config.set_generations(100); // 100
    dungeon_config.set_population_size(20);

    GeneticAlgorithm<ZombieTilesIndividual> m_ga;
    m_ga.run();
    dungeon = new RoomMap(m_ga.get_best()->get_map());
}

void get_corridors()
{
    //    d
}
