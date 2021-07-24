#pragma once

#include "dungeonconfig.h"
#include "individual.h"
#include "individualfactory.h"
#include <list>

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(DungeonConfig *dungeon_config,
                     IndividualFactory *individual_factory,
                     int population_size);
    void init();

    const std::list<Individual *> &get_population() const;

private:
    DungeonConfig *dungeon_config;
    IndividualFactory *individual_factory;
    std::list<Individual *> population;
    int generation;
    int population_size;
};
