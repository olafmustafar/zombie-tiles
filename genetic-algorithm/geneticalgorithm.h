#pragma once

#include "dungeonconfig.h"
#include "individual.h"
#include "individualfactory.h"
#include <list>

class GeneticAlgorithmImpl
{
public:
    GeneticAlgorithmImpl(int population_size);
    void init();

    const std::list<Individual*>& get_population() const;

private:
    virtual Individual* create_individual() const = 0;
    std::list<Individual*> m_population;
    int m_generation;
    int m_population_size;
};

template<typename IndividualType> class GeneticAlgorithm : public GeneticAlgorithmImpl
{
public:
    using GeneticAlgorithmImpl::GeneticAlgorithmImpl;

private:
    Individual* create_individual() const override { return new IndividualType; };
};
