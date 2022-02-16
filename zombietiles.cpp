#include "zombietiles.hpp"
#include "models/dungeonconfig.hpp"
#include "models/enemiesconfig.hpp"
#include "models/roommap.hpp"
#include "utils/logger.hpp"
#include "utils/randomgenerator.hpp"
#include "zombietiles-ga/dungeon/zombietilesga.hpp"
#include "zombietiles-ga/enemy/enemyindividual.h"
#include <algorithm>
#include <helpers/roommaphelper.hpp>
#include <utils/singleton.hpp>
#include <vector>

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

void generate_dungeon_enemies(RoomMap* dungeon, int& size, Enemy*& array)
{
    vector<Enemy> enemies;

    if (!dungeon->has_entities()) {
        EnemiesConfig& enemies_config = Singleton<EnemiesConfig>::get_instance();
        enemies_config.current_dungeon = dungeon;
        enemies_config.max_att_value = 100;
        enemies_config.min_att_value = 1;

        GeneticAlgorithm<EnemyIndividual> enemy_ga;
        enemy_ga.run();

        std::vector<Enemy> enemies = std::move(enemy_ga.get_best()->get_chromosome()->enemies);

        for (auto& enemy : enemies) {
            if ((*dungeon)[enemy.position] != RoomMap::EMPTY_ROOM) {
                dungeon->add_enemy(enemy);
            }
        }
    }

    enemies = dungeon->get_enemies();

    size = enemies.size();
    array = new Enemy[size];
    std::move(enemies.begin(), enemies.end(), array);
}

void generate_dungeon_player(RoomMap* dungeon, Entity*& player)
{
    if (!dungeon->has_player()) {
        RoomMapHelper::add_player_to(*dungeon);
    }

    player = new Entity { dungeon->get_player() };
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

void generate_dungeon_rooms(RoomMap* dungeon, int& size, Room*& array)
{
    size = dungeon->get_rooms().size();
    array = new Room[size];
    std::copy_n(dungeon->get_rooms().begin(), size, array);
}
