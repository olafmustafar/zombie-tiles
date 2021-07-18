#pragma once

#include "gene.h"
#include <QList>

class Individual
{
public:
    Individual();
    Individual(QList<Gene> genes);
    virtual ~Individual();
    virtual void mutate();
    virtual Individual *clone() const;
    virtual Individual *crossover() const;
    virtual double evaluate() const;
    void randomize() const;

protected:
    QList<Gene> genes;
    double current_fitness;
    double relative_fitness;
    double cumulative_fitness;
};

