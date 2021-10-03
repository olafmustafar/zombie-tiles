#include "geneticalgorithm.hpp"

#include <string>
#include <utils/logger.hpp>

GeneticAlgorithmImpl::GeneticAlgorithmImpl(int population_size)
    : m_generation(0)
    , m_population_size(population_size)
    , m_population({})
    , m_best(nullptr)
{
}

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

    evaluate();
    keep_best();

    Logger::doing("Sorting by value", [&]() { Logger::log() << "//TODO VAGABUNDO"; });

    Logger::done();
}

const std::list<IndividualImpl*>& GeneticAlgorithmImpl::get_population() const
{
    return m_population;
}

void GeneticAlgorithmImpl::evaluate()
{
    Logger::doing("Evaluating individuals");
    for (IndividualImpl* individual : m_population) {
        individual->evaluate();
        Logger::log() << "fitness:" + std::to_string(individual->get_fitness());
    }
    Logger::done();
}

void GeneticAlgorithmImpl::keep_best()
{
    Logger::doing("Keeping best individual");
    IndividualImpl* best = nullptr;

    for (IndividualImpl* individual : m_population) {
        if (!best || best->get_fitness() < individual->get_fitness()) {
            best = individual;
        }
    }

    delete m_best;
    m_best = create_individual(best);

    Logger::log() << "best: " << m_best->to_string();

    Logger::done();
    return;
}
