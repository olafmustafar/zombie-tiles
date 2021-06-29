#include "geneticalgorithm.h"

#include <iostream>
#include <utils/logger.h>

GeneticAlgorithm::GeneticAlgorithm(QList<Individual *> population)
    : population(population), generation(0)
{}

void GeneticAlgorithm::init()
{
    Logger::doing("Initializing population");

    generation = 0;
    for (Individual *i : population) {
        i->randomize();
    }

    Logger::done();
}
