#include "individual.h"

Individual::Individual()
    : m_chromosome(nullptr), m_current_fitness(0), m_relative_fitness(0), m_cumulative_fitness(0)
{}

Individual::~Individual() = default;

double Individual::evaluate() const
{
    return 0.0;
}

void Individual::init()
{
    m_chromosome = create_cromossome();
    m_chromosome->randomize();
}

Chromosome *Individual::get_chromosome() const
{
    return m_chromosome;
}

void Individual::set_chromosome(Chromosome *chromosome)
{
    m_chromosome = chromosome;
}
