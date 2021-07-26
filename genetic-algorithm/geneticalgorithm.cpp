#include "geneticalgorithm.h"

#include <iostream>
#include <utils/logger.h>

GeneticAlgorithmImpl::GeneticAlgorithmImpl(int population_size)
    : m_population({}), m_generation(0), m_population_size(population_size)
{}

void GeneticAlgorithmImpl::init()
{
    Logger::doing("Initializing population");

    m_generation = 0;

    for (int i = 0; i < m_population_size; ++i) {
        Individual* individual = create_individual();

        individual->init();
        m_population.push_back(individual);
    }

    Logger::done();
}

const std::list<Individual*>& GeneticAlgorithmImpl::get_population() const
{
    return m_population;
}
