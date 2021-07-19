#include "individual.h"

Individual::Individual()
    : chromosome(nullptr), current_fitness(0), relative_fitness(0), cumulative_fitness(0)
{}

Individual::~Individual() = default;

double Individual::evaluate() const
{
    return 0.0;
}

void Individual::init()
{
    this->chromosome = create_cromossome();
    this->chromosome->randomize();
}

Chromosome *Individual::get_chromosome() const
{
    return chromosome;
}

void Individual::set_chromosome(Chromosome *chromosome)
{
    this->chromosome = chromosome;
}
