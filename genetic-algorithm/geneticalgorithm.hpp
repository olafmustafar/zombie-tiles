#pragma once

#include <models/dungeonconfig.hpp>
#include "individual.hpp"
#include <list>

class GeneticAlgorithmImpl
{
public:
    GeneticAlgorithmImpl(int population_size);
    void init();
    void run(int generations);

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

    std::list<IndividualType*> get_population()
    {
        std::list<IndividualType*> individual_list;
        for (IndividualImpl* individual : GeneticAlgorithmImpl::get_population()) {
            individual_list.push_back(static_cast<IndividualType*>(individual));
        }
        return individual_list;
    };

private:
    IndividualImpl* create_individual() const override { return new IndividualType; };
};
