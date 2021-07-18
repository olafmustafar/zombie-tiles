#pragma once

#include "individual.h"

class IndividualFactory
{
public:
    virtual Individual *createIndividual() = 0;
};
