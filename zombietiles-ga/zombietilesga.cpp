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
    print();
}

void ZombieTilesGA::print()
{
    int index = 0;

    for (ZombieTilesIndividual* individual : m_ga.get_population()) {
        std::cout << "individuo: " << index++ << std::endl;
        std::cout << individual->to_string() << std::endl;
    }
}
