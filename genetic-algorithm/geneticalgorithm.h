#pragma once

#include "dungeonconfig.h"
#include "individual.h"
#include <list>

class GeneticAlgorithmImpl
{
public:
    GeneticAlgorithmImpl(int population_size);
    void init();

    const std::list<IndividualImpl*>& get_population() const;

private:
    virtual IndividualImpl* create_individual() const = 0;
    std::list<IndividualImpl*> m_population;
    int m_generation;
    int m_population_size;
};

template<typename IndividualType> class GeneticAlgorithm : public GeneticAlgorithmImpl
{
public:
    using GeneticAlgorithmImpl::GeneticAlgorithmImpl;

private:
    IndividualImpl* create_individual() const override { return new IndividualType; };
};
