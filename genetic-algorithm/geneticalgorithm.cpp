#include "geneticalgorithm.hpp"

#include <string>
#include <utils/logger.hpp>

GeneticAlgorithmImpl::GeneticAlgorithmImpl(int population_size)
    : m_population({}), m_generation(0), m_population_size(population_size)
{}

void GeneticAlgorithmImpl::init()
{
    Logger::doing("Initializing population");

    m_generation = 0;

    for (int i = 0; i < m_population_size; ++i) {
        IndividualImpl* individual = create_individual();
        individual->init();
        m_population.push_back(individual);
    }

    Logger::done();
}

void GeneticAlgorithmImpl::run(int generations)
{
    Logger::doing("Running for " + std::to_string(generations) + " generations");

    Logger::doing("Evaluating individuals", [&]() {
        for (int i = 0; i < generations; ++i) {
            for (IndividualImpl* individual : m_population) {
                individual->evaluate();
            }
        }
    });

    Logger::doing("Sorting by value", [&]() { Logger::log("//TODO VAGABUNDO"); });

    Logger::done();
}

const std::list<IndividualImpl*>& GeneticAlgorithmImpl::get_population() const
{
    return m_population;
}
