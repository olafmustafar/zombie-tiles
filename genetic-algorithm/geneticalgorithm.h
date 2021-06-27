#pragma once

#include "individual.h"

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(Individual individual, int population_size);
    void init();

private:
    QList<Individual *> population;
    double population_size;
    int generation;
};
