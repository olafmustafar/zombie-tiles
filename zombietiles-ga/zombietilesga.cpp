#include "zombietilesga.hpp"
#include "zombietileschromosome.hpp"
#include <helpers/graphhelper.hpp>
#include <helpers/tilemaphelper.hpp>
#include <models/tilemap.hpp>
#include <utils/logger.hpp>
#include <utils/randomgenerator.hpp>

#include <iostream>

namespace {
constexpr int POPULATION_SIZE = 20;
constexpr int GENERATION_SIZE = 20;
}

ZombieTilesGA::ZombieTilesGA()
    : m_ga(POPULATION_SIZE)
{
}

void ZombieTilesGA::run()
{
    // m_ga.init();
    // m_ga.run(GENERATION_SIZE);

    TileMap tilemap = TileMapHelper::create_tilemap();
    TileMapHelper::add_room_to(tilemap, Room(2, 4, 23, 15, Room::PlacementType::T));
    TileMapHelper::add_room_to(tilemap, Room(2, 4, 23, 15, Room::PlacementType::T));
    TileMapHelper::add_room_to(tilemap, Room(1, 14, 5, 15, Room::PlacementType::U));
    TileMapHelper::add_room_to(tilemap, Room(2, 4, 28, 16, Room::PlacementType::U));
    TileMapHelper::add_room_to(tilemap, Room(1, 21, 15, 8, Room::PlacementType::T));
    TileMapHelper::add_room_to(tilemap, Room(7, 17, 16, 12, Room::PlacementType::T));
    Logger::log(TileMapHelper::to_painted_map_string(tilemap));

    Logger::warn(std::to_string(tilemap.get_rooms().size()));
}

void ZombieTilesGA::print()
{
    int index = 0;

    for (ZombieTilesIndividual* individual : m_ga.get_population()) {
        std::cout << "individuo: " << index++ << std::endl;
        std::cout << individual->to_string() << std::endl;
    }
}
