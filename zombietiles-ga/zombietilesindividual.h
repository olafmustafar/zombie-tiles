#pragma once

#include <genetic-algorithm/individual.h>
#include "zombietileschromosome.h"

class ZombieTilesIndividual : public Individual<ZombieTilesChromosome>
{
public:
    ZombieTilesIndividual();
    ~ZombieTilesIndividual();
    double evaluate() const override;
};
