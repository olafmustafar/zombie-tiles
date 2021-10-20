#include "zombietiles.hpp"
#include "models/dungeonconfig.hpp"
#include "models/roommap.hpp"
#include "utils/logger.hpp"
#include "utils/randomgenerator.hpp"
#include "zombietiles-ga/zombietilesga.hpp"
#include <algorithm>
#include <helpers/roommaphelper.hpp>

namespace {
RoomMap* dungeon = nullptr;
Wall* walls = nullptr;
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

    delete dungeon;
    dungeon = new RoomMap(m_ga.get_best()->get_map());
}

void get_wall_array(int& size, Wall*& array)
{
    vector<Wall> wall_vector = RoomMapHelper::walls_of(*dungeon);
    for (auto wall : wall_vector) {
        cout << "a(" << wall.a.x << ", " << wall.a.y
             << ") => b(" << wall.b.x << ", " << wall.b.y << ")" << endl;
    }

    size = wall_vector.size();

    if (walls == nullptr) {
        walls = new Wall[size]();
    }

    std::move(wall_vector.begin(), wall_vector.end(), walls);
    array = walls;
}

void teste(int& length, Wall*& array)
{

    array = new Wall[3] {
        { { 0, 1 }, { 2, 3 } },
        { { 4, 5 }, { 6, 7 } },
        { { 8, 9 }, { 10, 11 } }
    };
    length = 3;
}
