#pragma once

#include "individual.h"
#include "individualfactory.h"

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(IndividualFactory *individual_factory, int population_size);
    void init();

    const QList<Individual *> &get_population() const;

private:
    IndividualFactory *individual_factory;
    QList<Individual *> population;
    int generation;
    int population_size;
};
