#include "zombietilesga.hpp"
#include "zombietileschromosome.hpp"
#include <helpers/graphhelper.hpp>
#include <helpers/roommaphelper.hpp>
#include <models/roommap.hpp>
#include <utils/logger.hpp>
#include <utils/randomgenerator.hpp>

#include <iostream>

namespace {
constexpr size_t CROMOSSOME_SIZE = 20;
constexpr int POPULATION_SIZE = 20;
constexpr int GENERATION_SIZE = 100;
}

ZombieTilesGA::ZombieTilesGA()
    : config(DungeonConfig::get_instance())
{
}

void ZombieTilesGA::run()
{

    //    DungeonConfig dungeon_config = DungeonConfig::get_instance(width, height);

    //    m_ga(POPULATION_SIZE);
    //    m_ga.initialize();
    //    m_ga.run(GENERATION_SIZE);

    //    TileMap tilemap = TileMapHelper::create_tilemap();
    //    TileMapHelper::add_room_to(tilemap, Room(15, 10, 13, 3, Room::PlacementType::U));
    //    TileMapHelper::add_room_to(tilemap, Room(13, 0, 4, 30, Room::PlacementType::T));
    //    TileMapHelper::add_room_to(tilemap, Room(5, 0, 24, 29, Room::PlacementType::T));
    //    TileMapHelper::add_room_to(tilemap, Room(12, 5, 15, 23, Room::PlacementType::U));
    //    TileMapHelper::add_room_to(tilemap, Room(18, 13, 2, 7, Room::PlacementType::T));
    //    Logger::log(TileMapHelper::to_painted_map_string(tilemap));
    //    Logger::warn(std::to_string(tilemap.get_rooms().size()));

    //    Logger::Log << "teste";
}

void ZombieTilesGA::print()
{
    int index = 0;

    for (ZombieTilesIndividual* individual : m_ga.get_population()) {
        std::cout << "individuo: " << index++ << std::endl;
        std::cout << individual->to_string() << std::endl;
    }
}
