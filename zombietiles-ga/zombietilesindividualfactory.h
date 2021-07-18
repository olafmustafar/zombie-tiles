#pragma once

#include "zombietilesindividual.h"
#include <genetic-algorithm/individualfactory.h>

class ZombieTilesIndividualFactory : public IndividualFactory
{
public:
    ZombieTilesIndividual *createIndividual() override;
};
