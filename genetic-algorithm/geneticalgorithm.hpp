#pragma once

#include "individual.hpp"
#include <list>
#include <models/dungeonconfig.hpp>

class GeneticAlgorithmImpl {
public:
    GeneticAlgorithmImpl(int population_size);
    void init();
    void run(int generations);
    const std::list<IndividualImpl*>& get_population() const;

private:
    int m_generation;
    int m_population_size;
    std::list<IndividualImpl*> m_population;
    IndividualImpl* m_best;

    virtual IndividualImpl* create_individual() const = 0;
    virtual IndividualImpl* create_individual(const IndividualImpl* individual) const = 0;

    void evaluate();
    void keep_best();
};

template <typename IndividualType>
class GeneticAlgorithm : public GeneticAlgorithmImpl {
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
    IndividualImpl* create_individual() const override
    {
        return new IndividualType;
    };

    IndividualImpl* create_individual(const IndividualImpl* individual) const override
    {
        return new IndividualType(*static_cast<const IndividualType*>(individual));
    };
};
