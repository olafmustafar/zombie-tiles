#include "individual.h"

Individual::Individual(QList<Gene> genes)
    : genes(genes), current_fitness(0), relative_fitness(0), cumulative_fitness(0)
{}

void Individual::randomize() const
{
    for (Gene gene : this->genes) {
        gene.randomize();
    }
}
