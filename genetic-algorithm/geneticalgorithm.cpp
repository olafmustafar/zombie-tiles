#include "geneticalgorithm.h"

#include <iostream>
#include <utils/logger.h>

GeneticAlgorithm::GeneticAlgorithm(IndividualFactory *individual_factory, int population_size)
    : individual_factory(individual_factory), population({}), generation(0),
      population_size(population_size)
{}

void GeneticAlgorithm::init()
{
    Logger::doing("Initializing population");

    this->generation = 0;

    for (int i = 0; i < this->population_size; ++i) {
        Individual *individual = this->individual_factory->createIndividual();
        individual->init();
        this->population.append(individual);
    }

    Logger::done();
}

const QList<Individual *> &GeneticAlgorithm::get_population() const
{
    return population;
}
