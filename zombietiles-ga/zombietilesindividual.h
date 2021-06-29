#pragma once

#include <genetic-algorithm/individual.h>

class ZombieTilesIndividual : public Individual
{
public:
    ~ZombieTilesIndividual();
    void mutate() override;
    Individual *clone() const override;
    Individual *crossover() const override;
    double evaluate() const override;
};
