#pragma once

#include <genetic-algorithm/geneticalgorithm.h>
#include <dungeonconfig.h>
#include "zombietilesindividual.h"

class ZombieTilesGA
{
public:
    ZombieTilesGA();
    void run();
    void print();

private:
    GeneticAlgorithm<ZombieTilesIndividual> m_ga;
};
