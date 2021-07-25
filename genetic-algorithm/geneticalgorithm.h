#pragma once

#include "dungeonconfig.h"
#include "individual.h"
#include "individualfactory.h"
#include <list>

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(IndividualFactory *individual_factory, int population_size);
    void init();

    const std::list<Individual *> &get_population() const;

private:
    IndividualFactory *m_individual_factory;
    std::list<Individual *> m_population;
    int m_generation;
    int m_population_size;
};
