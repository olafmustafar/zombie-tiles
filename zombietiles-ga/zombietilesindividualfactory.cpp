#include "zombietilesindividualfactory.h"

ZombieTilesIndividual *ZombieTilesIndividualFactory::createIndividual()
{
    return new ZombieTilesIndividual;
}
