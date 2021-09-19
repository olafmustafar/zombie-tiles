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
    // m_ga.init();
    // m_ga.run(GENERATION_SIZE);

    TileMap tilemap = TileMapHelper::create_tilemap();
    tilemap.addRoom(Room(0, 0, 1, 1, Room::PlacementType::T));
    tilemap.addRoom(Room(1, 0, 1, 1, Room::PlacementType::T));
    tilemap.addRoom(Room(0, 1, 2, 1, Room::PlacementType::T));
    tilemap.addRoom(Room(2, 0, 1, 2, Room::PlacementType::T));
    Logger::log(TileMapHelper::to_painted_map_string(tilemap));

    Graph graph = TileMapHelper::to_graph(tilemap);
    // for (vector<int>& vec : graph) {
    //     for (int val : vec) {
    //         Logger::log(std::to_string(val));
    //     }
    // }
}

void ZombieTilesGA::print()
{
    int index = 0;

    for (ZombieTilesIndividual* individual : m_ga.get_population()) {
        std::cout << "individuo: " << index++ << std::endl;
        std::cout << individual->to_string() << std::endl;
    }
}
