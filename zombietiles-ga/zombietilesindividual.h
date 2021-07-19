#pragma once

#include <genetic-algorithm/individual.h>

class ZombieTilesIndividual : public Individual
{
public:
    ZombieTilesIndividual();
    ~ZombieTilesIndividual();
    double evaluate() const override;
    Chromosome *create_cromossome() const override;
};
