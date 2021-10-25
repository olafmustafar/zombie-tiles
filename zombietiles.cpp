#include "zombietiles.hpp"
#include "models/dungeonconfig.hpp"
#include "models/roommap.hpp"
#include "utils/logger.hpp"
#include "utils/randomgenerator.hpp"
#include "zombietiles-ga/zombietilesga.hpp"
#include <algorithm>
#include <helpers/roommaphelper.hpp>

namespace {
//RoomMap* dungeon = nullptr;
//Wall* walls = nullptr;
}

RoomMap* generate_dungeon(const uint32_t width, const uint32_t height)
{
    DungeonConfig& dungeon_config = DungeonConfig::get_instance();
    dungeon_config.set_width(width);
    dungeon_config.set_height(height);
    dungeon_config.set_rooms_count(10); // 10
    dungeon_config.set_generations(100); // 100
    dungeon_config.set_population_size(20);

    GeneticAlgorithm<ZombieTilesIndividual> m_ga;
    m_ga.run();

    return new RoomMap(m_ga.get_best()->get_map());
}

void get_dungeon_matrix(RoomMap* dungeon, int& width, int& height, int**& array)
{
    array = dungeon->get_matrix();
    width = dungeon->get_width();
    height = dungeon->get_height();
}

void generate_wall_array(RoomMap* dungeon, int& size, Wall*& array)
{
    vector<Wall> wall_vector = RoomMapHelper::walls_of(*dungeon);

    size = wall_vector.size();
    array = new Wall[size]();
    std::move(wall_vector.begin(), wall_vector.end(), array);
}

void free_dungeon(RoomMap* dungeon)
{
    delete dungeon;
}

void free_wall_array(Wall* array)
{
    delete[] array;
}
