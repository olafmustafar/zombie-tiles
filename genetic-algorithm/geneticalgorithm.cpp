#include "geneticalgorithm.h"

#include <iostream>
#include <utils/logger.h>

GeneticAlgorithm::GeneticAlgorithm(IndividualFactory *individual_factory, int population_size)
    : m_individual_factory(individual_factory), m_population({}), m_generation(0),
      m_population_size(population_size)
{}

void GeneticAlgorithm::init()
{
    Logger::doing("Initializing population");

    m_generation = 0;

    for (int i = 0; i < m_population_size; ++i) {
        Individual *individual = m_individual_factory->createIndividual();

        individual->init();
        m_population.push_back(individual);
    }

    Logger::done();
}

const std::list<Individual *> &GeneticAlgorithm::get_population() const
{
    return m_population;
}
