#include "zombietiles.hpp"
#include "models/dungeonconfig.hpp"
#include "models/tilemap.hpp"
#include "utils/logger.hpp"
#include "utils/randomgenerator.hpp"
#include "zombietiles-ga/zombietilesga.hpp"

#include <helpers/tilemaphelper.hpp>

void ZombieTiles::generate_dungeon(const uint32_t width, const uint32_t height)
{
    DungeonConfig& dungeon_config = DungeonConfig::get_instance();
    dungeon_config.set_width(width);
    dungeon_config.set_height(height);
    dungeon_config.set_rooms_count(10); // 10
    dungeon_config.set_generations(100); // 100
    dungeon_config.set_population_size(20);

    /*

    TileMap tilemap = TileMapHelper::create_tilemap();
    TileMapHelper::add_room_to(tilemap, Room ( 1 ,11 ,24 ,2 ,Room::PlacementType::T ) );
    TileMapHelper::add_room_to(tilemap, Room ( 1 ,0 ,16 ,28 ,Room::PlacementType::T ) );
    TileMapHelper::add_room_to(tilemap, Room ( 21 ,1 ,4 ,18 ,Room::PlacementType::T ) );
    TileMapHelper::add_room_to(tilemap, Room ( 8 ,27 ,21 ,2 ,Room::PlacementType::T ) );
    TileMapHelper::add_room_to(tilemap, Room ( 1 ,3 ,8 ,22 ,Room::PlacementType::T ) );
    TileMapHelper::add_room_to(tilemap, Room ( 0 ,11 ,14 ,7 ,Room::PlacementType::U ) );
    TileMapHelper::add_room_to(tilemap, Room ( 22 ,2 ,8 ,20 ,Room::PlacementType::T ) );
    TileMapHelper::add_room_to(tilemap, Room ( 0 ,1 ,30 ,26 ,Room::PlacementType::U ) );
    TileMapHelper::add_room_to(tilemap, Room ( 23 ,10 ,2 ,11 ,Room::PlacementType::T ) );
    TileMapHelper::add_room_to(tilemap, Room ( 7 ,1 ,9 ,4 ,Room::PlacementType::T ) );

    cout << (TileMapHelper::to_painted_map_string(tilemap)) << endl;
    cout << (std::to_string(tilemap.get_rooms().size())) << endl;
    */

    GeneticAlgorithm<ZombieTilesIndividual> m_ga;
    m_ga.run();

    return;
}
