#pragma once

#include "chromosome.h"
#include <QList>

class Individual
{
public:
    Individual();
    void init();
    virtual ~Individual();
    virtual double evaluate() const;

    Chromosome *get_chromosome() const;
    void set_chromosome(Chromosome *chromosome);

protected:
    Chromosome *chromosome;
    double current_fitness;
    double relative_fitness;
    double cumulative_fitness;

    virtual Chromosome *create_cromossome() const = 0;
};

