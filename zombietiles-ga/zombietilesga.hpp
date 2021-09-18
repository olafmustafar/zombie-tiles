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
    GeneticAlgorithm<ZombieTilesIndividual> m_ga;
};
