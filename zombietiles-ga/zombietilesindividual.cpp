#include "zombietilesindividual.h"

#include "zombietileschromosome.h"

#include <utils/randomgenerator.h>

double ZombieTilesIndividual::evaluate() const
{
    ZombieTilesChromosome* chromosome = get_chromosome();

    return 0.00;
}

string ZombieTilesIndividual::to_string()
{
    return Individual<ZombieTilesChromosome>::get_chromosome()->to_string();
}
