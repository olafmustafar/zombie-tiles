#include "zombietilesga.h"
#include "zombietileschromosome.h"
#include <utils/logger.h>
#include <utils/randomgenerator.h>

#include <models/tilemap.h>

#include <iostream>

namespace {
constexpr int POPULATION_SIZE = 20;
}

ZombieTilesGA::ZombieTilesGA() : m_ga(POPULATION_SIZE) { }

void ZombieTilesGA::run()
{
    m_ga.init();
    m_ga.run(20);
}

void ZombieTilesGA::print()
{
    int index = 0;

    //    TileMap tile(10, 10);
    //    Room

    for (ZombieTilesIndividual* individual : m_ga.get_population()) {
        std::cout << "individuo: " << index++ << std::endl;
        std::cout << individual->to_string() << std::endl;

        //        for (RoomGene& gene : genes)
        //            gene.get_room().print();
        //    }
    }
}
