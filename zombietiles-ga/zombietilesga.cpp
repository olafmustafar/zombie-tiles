#include "zombietilesga.h"
#include "zombietileschromosome.h"
#include <helpers/tilemaphelper.h>
#include <models/tilemap.h>
#include <utils/logger.h>
#include <utils/randomgenerator.h>

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
    TileMap map = TileMapHelper::create_tilemap();
    map.addRoom(Room(4, 0, 20, 20, Room::PlacementType::U));
    // map.addRoom(Room(4, 0, 3, 3, Room::PlacementType::T));
    map.addRoom(Room(8, 0, 3, 19, Room::PlacementType::T));
    // map.addRoom(Room(12, 0, 3, 20, Room::PlacementType::U));
    // map.addRoom(Room(4, 0, 3, 10, Room::PlacementType::T));
    std::cout << map.to_string() << endl;
    int n = TileMapHelper::count_rooms(map);
    std::cout << "Room count: " << n << endl;
    // m_ga.init();
    // m_ga.run(GENERATION_SIZE);
    // print();
}

void ZombieTilesGA::print()
{
    int index = 0;

    for (ZombieTilesIndividual* individual : m_ga.get_population()) {
        std::cout << "individuo: " << index++ << std::endl;
        std::cout << individual->to_string() << std::endl;
    }
}
