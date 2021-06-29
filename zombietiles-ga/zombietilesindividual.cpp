#include "zombietilesindividual.h"

ZombieTilesIndividual::~ZombieTilesIndividual() = default;

void ZombieTilesIndividual::mutate()
{
    //TODO
}

Individual *ZombieTilesIndividual::clone() const
{
    //TODO
    return new ZombieTilesIndividual(*this);
}

Individual *ZombieTilesIndividual::crossover() const
{
    //TODO
    return nullptr;
}

double ZombieTilesIndividual::evaluate() const
{
    //TODO
    return 0.00;
}
