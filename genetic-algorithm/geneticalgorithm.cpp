#include "geneticalgorithm.hpp"

#include <algorithm>
#include <string>
#include <utils/logger.hpp>
#include <utils/randomgenerator.hpp>

GeneticAlgorithmImpl::GeneticAlgorithmImpl(size_t population_size)
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
    m_population.reserve(m_population_size);

    for (size_t i = 0; i < m_population_size; ++i) {
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

    for (int i = 0; i < generations; ++i) {
        Logger::log() << "---------generation:" << i << "---------";
        select();
    }

    Logger::done();
}

const vector<IndividualImpl*>& GeneticAlgorithmImpl::get_population() const
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

void GeneticAlgorithmImpl::select()
{
    Logger::doing("Selecting");

    double total = accumulate(m_population.cbegin(), m_population.cend(), 0.00, [&](const double& total, const IndividualImpl* individual) {
        return total + individual->get_fitness();
    });

    //    for (const IndividualImpl* individual : m_population) {
    //        total += individual->get_fitness();
    //    }

    for (size_t i = 0; i < m_population_size; ++i) {
        IndividualImpl* individual = m_population[i];
        individual->set_relative_fitness(individual->get_fitness() / total);
        if (i == 0) {
            individual->set_cumulative_fitness(individual->get_relative_fitness());
        } else {
            individual->set_cumulative_fitness(m_population[i - 1]->get_cumulative_fitness() + individual->get_relative_fitness());
        }
    }

    vector<IndividualImpl*> new_population { m_population };

    for (size_t i = 0; i < m_population_size; ++i) {
        double p = RandomGenerator::random_between(0.0, 1.0);
        if (p < m_population[0]->get_cumulative_fitness()) {
            new_population[i] = m_population[0];
        } else {
            for (size_t j = 0; j < m_population_size; j++) {
                if (m_population[j]->get_cumulative_fitness() <= p && p < m_population[j + 1]->get_cumulative_fitness()) {
                    new_population[i] = m_population[j + 1];
                }
            }
        }
    }

    m_population = new_population;

    Logger::done();
}
