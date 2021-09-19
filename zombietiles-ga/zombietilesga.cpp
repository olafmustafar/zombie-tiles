#include "zombietilesga.hpp"
#include "zombietileschromosome.hpp"
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
    m_ga.init();
    m_ga.run(GENERATION_SIZE);

    // TileMap tilemap = TileMapHelper::create_tilemap();

    // Logger::warn(std::to_string(TileMapHelper::count_rooms(tilemap)));
    // Logger::warn(TileMapHelper::to_painted_map_string(tilemap));

    // tilemap.addRoom( Room( 15 , 10 ,13 , 3 ,Room::PlacementType::U ) );
    // tilemap.addRoom( Room( 13 , 0 ,4 , 30, Room::PlacementType::T )); 
    // tilemap.addRoom( Room( 5 , 0 ,24 , 29, Room::PlacementType::T )); 
    // tilemap.addRoom( Room( 12 , 5 ,15 , 23, Room::PlacementType::U )); 
    // tilemap.addRoom( Room( 18 , 13 ,2 , 7 ,Room::PlacementType::T )); 
    
    // Logger::warn(std::to_string(tilemap.get_rooms().size()));
    // Logger::warn(std::to_string(TileMapHelper::count_rooms(tilemap)));
    // Logger::warn(tilemap.to_string());
    // Logger::warn(TileMapHelper::to_painted_map_string(tilemap));
}

void ZombieTilesGA::print()
{
    int index = 0;

    for (ZombieTilesIndividual* individual : m_ga.get_population()) {
        std::cout << "individuo: " << index++ << std::endl;
        std::cout << individual->to_string() << std::endl;
    }
}
