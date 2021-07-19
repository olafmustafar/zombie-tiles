#include "zombietilesindividual.h"

#include "zombietileschromosome.h"

ZombieTilesIndividual::ZombieTilesIndividual() = default;

ZombieTilesIndividual::~ZombieTilesIndividual() = default;

double ZombieTilesIndividual::evaluate() const
{
    //TODO
    return 0.00;
}

Chromosome *ZombieTilesIndividual::create_cromossome() const
{
    return new ZombieTilesChromosome;
}
