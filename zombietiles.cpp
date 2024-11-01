#include "zombietiles.hpp"
#include "dungeonrepository.hpp"
#include "helpers/graphhelper.hpp"
#include "helpers/roommaphelper.hpp"
#include "models/dungeon.hpp"
#include "models/dungeonconfig.hpp"
#include "models/enemiesconfig.hpp"
#include "models/enemypool.hpp"
#include "utils/logger.hpp"
#include "utils/randomgenerator.hpp"
#include "zombietiles-ga/dungeon/zombietilesga.hpp"
#include "zombietiles-ga/enemy/enemyindividual.h"
#include <algorithm>
#include <helpers/roommaphelper.hpp>
#include <utils/singleton.hpp>
#include <vector>
#include <zombietiles-ga/enemy-v2/enemyindividualv2.hpp>

void set_population_size(size_t size)
{
    DungeonConfig::get_instance().population_size = size;
}

void set_number_of_iterations(size_t number_of_iterations)
{
    DungeonConfig::get_instance().number_of_iterations = number_of_iterations;
}

void set_number_of_iterations_without_change_limit(size_t number_of_iterations)
{
    DungeonConfig::get_instance().iterations_without_change_limit = number_of_iterations;
}

Dungeon* generate_dungeon(const uint32_t width, const uint32_t height)
{
    Logger::setLoggin(false);

    DungeonConfig& dungeon_config = DungeonConfig::get_instance();
    dungeon_config.set_width(width);
    dungeon_config.set_height(height);
    dungeon_config.set_rooms_count(5);
    dungeon_config.number_of_iterations = 300;
    dungeon_config.population_size = 200;

    GeneticAlgorithm<ZombieTilesIndividual> m_ga;
    m_ga.run();
    return new Dungeon(m_ga.get_best()->get_map());
}

Dungeon* generate_dungeon2(const uint32_t room_count, const uint32_t width, const uint32_t height)
{
    Logger::setLoggin(false);

    DungeonConfig& dungeon_config = DungeonConfig::get_instance();
    dungeon_config.set_width(width);
    dungeon_config.set_height(height);
    dungeon_config.set_rooms_count(room_count);
    dungeon_config.set_height(height);
    dungeon_config.iterations_without_change_limit = -1;

    GeneticAlgorithm<ZombieTilesIndividual> m_ga;
    m_ga.run();
    return new Dungeon(m_ga.get_best()->get_map());
}

void get_dungeon_matrix(Dungeon* dungeon, int& width, int& height, int**& array)
{
    const DungeonMatrix& matrix = dungeon->get_matrix();
    array = matrix.data();
    width = matrix.width();
    height = matrix.height();
}

void generate_dungeon_enemies(Dungeon* dungeon, int& size, Enemy*& array)
{
    Logger::setLoggin(false);

    vector<Enemy> enemies;

    if (!dungeon->has_enemies()) {
        DungeonConfig& dungeon_config = DungeonConfig::get_instance();
        dungeon_config.set_width(dungeon->width());
        dungeon_config.set_height(dungeon->height());
        dungeon_config.set_rooms_count(dungeon->rooms().size());

        EnemiesConfig& enemies_config = Singleton<EnemiesConfig>::get_instance();
        enemies_config.current_dungeon = dungeon;
        enemies_config.max_att = 100;
        enemies_config.min_att = 1;

        GeneticAlgorithm<EnemyIndividual> enemy_ga;
        enemy_ga.run();

        std::vector<Enemy> enemies = enemy_ga.get_best()->get_chromosome()->to_enemies(dungeon->get_matrix());

        dungeon->set_enemies(std::move(enemies));
    }

    enemies = dungeon->get_enemies();

    size = enemies.size();
    array = new Enemy[size];
    std::move(enemies.begin(), enemies.end(), array);
}

void generate_dungeon_enemies_v2(Dungeon* dungeon, int& size, Enemy*& array, size_t pool_size)
{
    Logger::setLoggin(false);

    DungeonConfig& dungeon_config = DungeonConfig::get_instance();
    if (!dungeon->has_enemies() && dungeon_config.population_size) {
        dungeon_config.set_width(dungeon->width());
        dungeon_config.set_height(dungeon->height());
        dungeon_config.set_rooms_count(dungeon->rooms().size());

        EnemiesConfig& enemies_config = St<EnemiesConfig>;
        enemies_config.current_dungeon = dungeon;
        enemies_config.max_att = 100;
        enemies_config.min_att = 1;

        St<EnemyPool> = EnemyPool::make_enemy_pool(pool_size);

        GeneticAlgorithm<V2::EnemyIndividual> enemy_ga;
        enemy_ga.run();

        dungeon->set_enemies(std::move(enemy_ga.get_best()->to_enemies(dungeon->get_matrix())));
    }

    std::vector<Enemy> enemies = dungeon->get_enemies();

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
    str = new char[size + 1];
    std::copy_n(description.c_str(), size + 1, str);
}

void generate_dungeon_rooms(Dungeon* dungeon, int& size, Room*& array)
{
    auto& matrix = dungeon->get_matrix();
    auto& rooms = dungeon->rooms();

    for (size_t x = 0; x < matrix.width(); x++) {
        for (size_t y = 0; y < matrix.height(); y++) {
            if (matrix[x][y] == DungeonMatrix::EMPTY) {
                continue;
            }
            rooms[matrix[x][y]].is_placed = true;
        }
    }

    size = dungeon->get_rooms().size();
    array = new Room[size];
    std::copy_n(dungeon->get_rooms().begin(), size, array);
}

void get_dungeon_distances_graph(Dungeon* dungeon, int& width, int& height, int**& array)
{
    Graph graph = RoomMapHelper::to_graph(dungeon->get_matrix());
    std::vector<std::vector<int>> distances = GraphHelper::distances_of(graph);

    width = distances.size();
    height = distances.front().size();
    array = new int*[width];
    size_t i = 0;
    for (std::vector<int> row : distances) {
        int* new_row = new int[row.size()];
        std::copy_n(row.begin(), row.size(), new_row);
        array[i++] = new_row;
    }
}

Dungeon* load_dungeon(const char* path)
{
    return DungeonRepository::load(path);
}

void save_dungeon(const Dungeon& dungeon, const char* path)
{
    DungeonRepository::save(dungeon, path);
}

DungeonMetadata generate_dungeon_metadata(Dungeon* dungeon)
{
    return RoomMapHelper::calculate_dungeon_metadata(*dungeon);
}

int ping()
{
    return 1;
}
