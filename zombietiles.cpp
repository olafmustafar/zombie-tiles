#include "zombietiles.hpp"
#include "models/dungeonconfig.hpp"
#include "models/roommap.hpp"
#include "utils/logger.hpp"
#include "utils/randomgenerator.hpp"
#include "zombietiles-ga/zombietilesga.hpp"
#include <algorithm>
#include <helpers/roommaphelper.hpp>

RoomMap* generate_dungeon(const uint32_t width, const uint32_t height)
{
    DungeonConfig& dungeon_config = DungeonConfig::get_instance();
    dungeon_config.set_width(width);
    dungeon_config.set_height(height);
    dungeon_config.set_rooms_count(10);
    dungeon_config.set_generations(100);
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

void generate_dungeon_entities(RoomMap* dungeon, int& size, Entity*& array)
{
    vector<Entity> entity_vec;

    if (!dungeon->has_entities()) {
        RoomMapHelper::generate_entities(*dungeon);
    }

    entity_vec = dungeon->get_entities();

    size = entity_vec.size();
    array = new Entity[size];
    std::move(entity_vec.begin(), entity_vec.end(), array);
}

void generate_dungeon_doors(RoomMap* dungeon, int& size, Door*& array)
{
    vector<Door> doors_vec;
    if (dungeon->get_doors().empty()) {
        doors_vec = RoomMapHelper::generate_doors(*dungeon);
    } else {
        doors_vec = dungeon->get_doors();
    }

    size = doors_vec.size();
    array = new Door[size];
    std::move(doors_vec.begin(), doors_vec.end(), array);
}

void generate_dungeon_walls(RoomMap* dungeon, int& size, Wall*& array)
{
    vector<Wall> wall_vector = RoomMapHelper::walls_of(*dungeon, RoomMapHelper::generate_doors(*dungeon));

    size = wall_vector.size();
    array = new Wall[size];
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

void set_seed(int seed)
{
    Random::set_seed(seed);
}

void generate_dungeon_description(RoomMap* dungeon, int& size, char*& str)
{
    std::string description = dungeon->to_string();

    size = description.length();
    str = new char[size];
    std::copy_n(description.begin(), size, str);
}
