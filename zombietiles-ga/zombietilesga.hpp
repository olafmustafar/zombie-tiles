#pragma once

#include <genetic-algorithm/geneticalgorithm.hpp>
#include <models/dungeonconfig.hpp>
#include "zombietilesindividual.hpp"

class ZombieTilesGA
{
public:
    ZombieTilesGA();
    void run();
    void print();

private:
    DungeonConfig config;
    GeneticAlgorithm<ZombieTilesIndividual> m_ga;
};
