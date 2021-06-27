#pragma once

#include "gene.h"
#include <QList>

class Individual
{
public:
    Individual(QList<Gene> genes);

    void randomize() const;
    virtual void crossover();
    virtual void mutate();

private:
    QList<Gene> genes;
    double current_fitness;
    double relative_fitness;
    double cumulative_fitness;
};

