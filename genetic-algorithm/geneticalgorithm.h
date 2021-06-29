#pragma once

#include "individual.h"

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(QList<Individual *> population);
    void init();

private:
    QList<Individual *> population;
    int generation;
};
