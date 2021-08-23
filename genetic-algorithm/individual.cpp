#include "individual.h"

IndividualImpl::IndividualImpl()
    : m_chromosome(nullptr), m_current_fitness(0), m_relative_fitness(0), m_cumulative_fitness(0)
{
}

IndividualImpl::~IndividualImpl()
{
    delete m_chromosome;
};

void IndividualImpl::init()
{
    m_chromosome = create_cromossome();
    m_chromosome->randomize();
}

double IndividualImpl::evaluate() const
{
    return 0.0;
}

Chromosome* IndividualImpl::get_chromosome() const
{
    return m_chromosome;
}

void IndividualImpl::set_chromosome(Chromosome* chromosome)
{
    m_chromosome = chromosome;
}
