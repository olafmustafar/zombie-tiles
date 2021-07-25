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
    Chromosome *m_chromosome;
    double m_current_fitness;
    double m_relative_fitness;
    double m_cumulative_fitness;

    virtual Chromosome *create_cromossome() const = 0;
};

