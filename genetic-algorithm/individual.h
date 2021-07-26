#pragma once

#include "chromosome.h"
#include <QList>

class IndividualImpl
{
public:
    IndividualImpl();
    virtual ~IndividualImpl();

    void init();
    virtual double evaluate() const;

    Chromosome *get_chromosome() const;
    void set_chromosome(Chromosome* chromosome);

private:
    Chromosome *m_chromosome;
    double m_current_fitness;
    double m_relative_fitness;
    double m_cumulative_fitness;

    virtual Chromosome *create_cromossome() const = 0;
};

template<typename ChromosomeType> class Individual : IndividualImpl
{
public:
    using IndividualImpl::IndividualImpl;
    ~Individual() override = default;

private:
    Chromosome* create_cromossome() const override { return new ChromosomeType; }
};
