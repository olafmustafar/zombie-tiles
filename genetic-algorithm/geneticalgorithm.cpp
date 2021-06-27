#include "geneticalgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(Individual individual, int population_size) : generation(0)
{
    for (int i = 0; i < population_size; i++) {
        this->population.append(new Individual(individual));
    }
}

void GeneticAlgorithm::init()
{
    generation = 0;
    for (Individual *i : population) {
        i->randomize();
    }
}
