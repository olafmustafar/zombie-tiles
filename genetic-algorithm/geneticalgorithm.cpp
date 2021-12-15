#include "geneticalgorithm.hpp"

#include <algorithm>
#include <cassert>
#include <string>
#include <utils/logger.hpp>
#include <utils/randomgenerator.hpp>

GeneticAlgorithmImpl::GeneticAlgorithmImpl()
    : m_population_size(0)
    , m_population({})
    , m_best(nullptr)
{
}

GeneticAlgorithmImpl::~GeneticAlgorithmImpl()
{
    for (IndividualImpl* individual : m_population) {
        delete individual;
    }

    delete m_best;
}

void GeneticAlgorithmImpl::run()

{
    uint32_t generations = DungeonConfig::get_instance().get_generations();

    Logger::log() << "Running for " << generations << " generations";

    initialize();
    evaluate();
    keep_best();

    for (uint32_t i = 0; i < generations; ++i) {
        Logger::log() << "---------generation:" << i << "---------";
        select();
        crossover();
        mutate();
        report(i);
        evaluate();
        elitist();
    }

    Logger::log() << "Best: " << m_best->to_string();
}

const vector<IndividualImpl*>& GeneticAlgorithmImpl::get_population() const
{
    return m_population;
}

IndividualImpl* GeneticAlgorithmImpl::get_best() const
{
    return m_best;
}

void GeneticAlgorithmImpl::initialize()
{
    Logger::doing("Initializing population");

    m_population_size = DungeonConfig::get_instance().get_population_size();
    m_population.reserve(m_population_size);

    for (size_t i = 0; i < m_population_size; ++i) {
        IndividualImpl* individual = create_individual();
        individual->init();
        m_population.push_back(individual);
    }

    Logger::done();
}

void GeneticAlgorithmImpl::evaluate()
{
    Logger::doing("Evaluating individuals");

    for (IndividualImpl* individual : m_population) {
        individual->evaluate();
        Logger::log() << "[" << individual << "]'s fitness: " + std::to_string(individual->get_fitness());
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

    Logger::log() << "Best: [" << m_best << "]";
    Logger::log() << m_best->to_string();

    Logger::done();
    return;
}

void GeneticAlgorithmImpl::select()
{
    Logger::doing("Selecting");

    double total = accumulate(m_population.cbegin(), m_population.cend(), 0.00, [&](const double& total, const IndividualImpl* individual) {
        return total + individual->get_fitness();
    });

    for (size_t i = 0; i < m_population_size; ++i) {
        IndividualImpl* individual = m_population[i];
        individual->set_relative_fitness(individual->get_fitness() / total);
        if (i == 0) {
            individual->set_cumulative_fitness(individual->get_relative_fitness());
        } else {
            individual->set_cumulative_fitness(m_population[i - 1]->get_cumulative_fitness() + individual->get_relative_fitness());
        }
    }

    vector<IndividualImpl*> new_population(m_population.size());

    for (size_t i = 0; i < m_population_size; ++i) {
        double p = Random::random_between(0.0, 1.0);

        if (p < m_population.front()->get_cumulative_fitness()) {
            new_population[i] = create_individual(m_population[0]);
        } else {
            for (size_t j = 0; j < m_population_size - 1; ++j) {
                if (m_population[j]->get_cumulative_fitness() <= p && p < m_population[j + 1]->get_cumulative_fitness()) {
                    new_population[i] = create_individual(m_population[j + 1]);
                }
            }
        }
    }

    for (size_t i = 0; i < m_population.size(); ++i) {
        delete m_population[i];
    }

    m_population = std::move(new_population);

    for (IndividualImpl* individual : m_population) {
        Logger::log() << "New individual: [" << individual << "]";
    }

    Logger::done();
}

void GeneticAlgorithmImpl::crossover()
{
    Logger::doing("Crossing individuals");
    const double crossover_chance = 0.8;

    IndividualImpl* first = nullptr;

    for (IndividualImpl* second : m_population) {
        double x = Random::random_between(0.0, 1.0);

        if (x < crossover_chance) {
            if (first) {
                first->crossover(second);
                Logger::log() << "Crossing over: [" << first << "] X [" << second << "]";
                first = nullptr;
            } else {
                first = second;
            }
        }
    }
    Logger::done();
}

void GeneticAlgorithmImpl::mutate()
{
    Logger::doing("Mutating individuals");
    for (IndividualImpl* individual : m_population) {
        double mutation_chance = Random::random_between(0.0, 1.0);
        if (mutation_chance < 0.1) {
            Logger::log() << "Mutating individual:[" << individual << "]";
            individual->mutate();
        }
    }
    Logger::done();
}

void GeneticAlgorithmImpl::elitist()
{
    Logger::doing("Keeping best individual");

    IndividualImpl* best = nullptr;
    IndividualImpl* worst = nullptr;

    for (IndividualImpl* individual : m_population) {
        if (!best || best->get_fitness() < individual->get_fitness()) {
            best = individual;
        }

        if (!worst || worst->get_fitness() > individual->get_fitness()) {
            worst = individual;
        }
    }

    assert(best);
    assert(worst);

    if (best->get_fitness() > m_best->get_fitness()) {
        Logger::log() << "Replacing best [" << m_best << "] with better individual of current [" << best << "]";
        delete m_best;
        m_best = create_individual(best);
    } else {
        Logger::log() << "Replacing worst of current population [" << worst << "] with best of the previous [" << best << "]";
        replace(m_population.begin(), m_population.end(), worst, m_best);
        delete worst;
        m_best = create_individual(m_best);
    }

    Logger::done();
}

void GeneticAlgorithmImpl::report(int generation) const
{
    Logger::doing("Reporting");
    cout << "generation: " << generation << "| best: " << m_best->get_fitness() << endl;

    Logger::done();
}
