#pragma once

#include <genetic-algorithm/individual.h>
#include "zombietileschromosome.h"

class ZombieTilesIndividual : public Individual<ZombieTilesChromosome>
{
public:
    double evaluate() const override;
    string to_string();
};
