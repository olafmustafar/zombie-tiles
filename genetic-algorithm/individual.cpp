#include "individual.h"

Individual::Individual() : genes({}), current_fitness(0), relative_fitness(0), cumulative_fitness(0)
{}

Individual::Individual(QList<Gene> genes)
    : genes(genes), current_fitness(0), relative_fitness(0), cumulative_fitness(0)
{}

Individual::~Individual() = default;

void Individual::randomize() const
{
    for (Gene gene : this->genes) {
        gene.randomize();
    }
}

Individual *Individual::crossover() const
{
    return nullptr;
}

double Individual::evaluate() const
{
    return 0.0;
}

Individual *Individual::clone() const
{
    return nullptr;
}

void Individual::mutate() {}
