#pragma once

#include "chromosome.hpp"

class IndividualImpl
{
public:
    IndividualImpl();
    virtual ~IndividualImpl();

    void init();
    void evaluate();

    void get_fitness() const;
    void set_relative_fitness();
    void set_cumulative_fitness();

    Chromosome *get_chromosome() const;
    void set_chromosome(Chromosome* chromosome);

private:
    Chromosome *m_chromosome;
    double m_current_fitness;
    double m_relative_fitness;
    double m_cumulative_fitness;

    virtual double calculate_fitness() const = 0;
    virtual Chromosome *create_cromossome() const = 0;
};

template<typename ChromosomeType> class Individual : public IndividualImpl
{
public:
    ~Individual() override = default;

    ChromosomeType* get_chromosome() const
    {
        return static_cast<ChromosomeType*>(IndividualImpl::get_chromosome());
    };

private:
    Chromosome* create_cromossome() const override { return new ChromosomeType; }
};
