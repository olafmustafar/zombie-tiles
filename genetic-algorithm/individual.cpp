#include "individual.hpp"

IndividualImpl::IndividualImpl()
    : m_chromosome(nullptr)
    , m_current_fitness(0)
    , m_relative_fitness(0)
    , m_cumulative_fitness(0)
{
}

IndividualImpl::~IndividualImpl()
{
    delete m_chromosome;
}

void IndividualImpl::init()
{
    m_chromosome = create_cromossome();
    m_chromosome->randomize();
}

void IndividualImpl::evaluate()
{
    m_current_fitness = calculate_fitness();
}

double IndividualImpl::get_fitness() const
{
    return m_current_fitness;
}
void IndividualImpl::set_relative_fitness(double relative_fitness)
{
    m_relative_fitness = relative_fitness;
}
void IndividualImpl::set_cumulative_fitness(double cumulative_fitness)
{
    m_cumulative_fitness = cumulative_fitness;
}

Chromosome* IndividualImpl::get_chromosome() const
{
    return m_chromosome;
}

void IndividualImpl::set_chromosome(Chromosome* chromosome)
{
    m_chromosome = chromosome;
}
