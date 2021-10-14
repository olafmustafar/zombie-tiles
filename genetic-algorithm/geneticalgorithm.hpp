#pragma once

#include "individual.hpp"
#include <models/dungeonconfig.hpp>
#include <vector>

class GeneticAlgorithmImpl {
public:
    GeneticAlgorithmImpl();
    void run();
    const vector<IndividualImpl*>& get_population() const;

private:
    int m_generation;
    size_t m_population_size;
    vector<IndividualImpl*> m_population;
    IndividualImpl* m_best;

    virtual IndividualImpl* create_individual() const = 0;
    virtual IndividualImpl* create_individual(const IndividualImpl* individual) const = 0;

    void initialize();
    void evaluate();
    void keep_best();
    void select();
    void crossover();
    void mutate();
    void elitist();
    void report(int generation) const;
};

template <typename IndividualType>
class GeneticAlgorithm : public GeneticAlgorithmImpl {
public:
    using GeneticAlgorithmImpl::GeneticAlgorithmImpl;

    vector<IndividualType*> get_population()
    {
        vector<IndividualType*> individual_list;
        for (IndividualImpl* individual : GeneticAlgorithmImpl::get_population()) {
            individual_list.push_back(static_cast<IndividualType*>(individual));
        }
        return individual_list;
    }

private:
    IndividualImpl* create_individual() const override
    {
        return new IndividualType;
    }

    IndividualImpl* create_individual(const IndividualImpl* individual) const override
    {
        return new IndividualType(*static_cast<const IndividualType*>(individual));
    }
};
