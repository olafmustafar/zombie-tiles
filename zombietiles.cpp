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

Dungeon* generate_dungeon(const uint32_t width, const uint32_t height)
{
    Logger::setLoggin(false);

    DungeonConfig& dungeon_config = DungeonConfig::get_instance();
    dungeon_config.set_width(width);
    dungeon_config.set_height(height);
    dungeon_config.set_rooms_count(10);
    dungeon_config.set_generations(100);
    dungeon_config.set_population_size(200);

    //    RoomMap rm(10, 10);
    //    RoomMapHelper::add_room_to(rm, Room { 0, 0, 1, 10, Room::PlacementType::T });
    //    RoomMapHelper::add_room_to(rm, Room { 1, 4, 5, 5, Room::PlacementType::T });
    //    string str = RoomMapHelper::to_painted_map_string(rm);
    //    std::cout << str << std::endl;

    //    RoomMap rm2(10, 10);
    //    rm2.add_room({ 0, 0, 1, 10, Room::PlacementType::T });
    //    rm2.add_room({ 1, 4, 5, 5, Room::PlacementType::T });
    //    DungeonMatrix matrix = RoomMapHelper::generate_dungeon_matrix(rm2);
    //    string mstr = RoomMapHelper::to_painted_map_string(matrix);
    //    std::cout << mstr << std::endl;

    GeneticAlgorithm<ZombieTilesIndividual> m_ga;
    m_ga.run();

    return new Dungeon(m_ga.get_best()->get_map());
}

void get_dungeon_matrix(Dungeon* dungeon, int& width, int& height, int**& array)
{
    array = dungeon->get_matrix();
    width = dungeon->get_width();
    height = dungeon->get_height();
}

void generate_dungeon_enemies(Dungeon* dungeon, int& size, Enemy*& array)
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
            if ((*dungeon)[enemy.position] != Dungeon::EMPTY_ROOM) {
                dungeon->add_enemy(enemy);
            }
        }
    }

    enemies = dungeon->get_enemies();

    size = enemies.size();
    array = new Enemy[size];
    std::move(enemies.begin(), enemies.end(), array);
}

void generate_dungeon_player(Dungeon* dungeon, Entity*& player)
{
    if (!dungeon->has_player()) {
        RoomMapHelper::add_player_to(*dungeon);
    }

    player = new Entity { dungeon->get_player() };
}

void generate_dungeon_doors(Dungeon* dungeon, int& size, Door*& array)
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

void generate_dungeon_walls(Dungeon* dungeon, int& size, Wall*& array)
{
    vector<Wall> wall_vector = RoomMapHelper::walls_of(*dungeon, RoomMapHelper::generate_doors(*dungeon));

    size = wall_vector.size();
    array = new Wall[size];
    std::move(wall_vector.begin(), wall_vector.end(), array);
}

void free_dungeon(Dungeon* dungeon)
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

void generate_dungeon_description(Dungeon* dungeon, int& size, char*& str)
{
    std::string description = dungeon->to_string();

    size = description.length();
    str = new char[size];
    std::copy_n(description.begin(), size, str);
}

void generate_dungeon_rooms(Dungeon* dungeon, int& size, Room*& array)
{
    size = dungeon->get_rooms().size();
    array = new Room[size];
    std::copy_n(dungeon->get_rooms().begin(), size, array);
}
