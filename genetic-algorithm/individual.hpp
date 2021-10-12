#pragma once

#include "chromosome.hpp"
#include <string>

using namespace std;

class IndividualImpl {
public:
    IndividualImpl();
    virtual ~IndividualImpl();

    void init();
    void evaluate();

    double get_fitness() const;
    void set_relative_fitness(double relative_fitness);
    double get_relative_fitness() const;
    void set_cumulative_fitness(double cumulative_fitness);
    double get_cumulative_fitness() const;

    Chromosome* get_chromosome() const;
    void set_chromosome(Chromosome* chromosome);
    virtual string to_string() const;
    virtual void crossover(IndividualImpl* other) = 0;
    virtual void mutate() = 0;

private:
    Chromosome* m_chromosome;
    double m_current_fitness;
    double m_relative_fitness;
    double m_cumulative_fitness;

    virtual double calculate_fitness() const = 0;
    virtual Chromosome* create_cromossome() const = 0;
};

template <typename ChromosomeType>
class Individual : public IndividualImpl {
public:
    Individual() = default;
    ~Individual() override = default;

    Individual(const Individual<ChromosomeType>& other)
        : IndividualImpl(other)
    {
        set_chromosome(new ChromosomeType(*other.get_chromosome()));
    }

    Individual(Individual<ChromosomeType>&& other)
        : IndividualImpl(std::move(other))
    {
        set_chromosome(other.get_chromosome());
        other.set_chromosome(nullptr);
    }

    ChromosomeType* get_chromosome() const
    {
        return static_cast<ChromosomeType*>(IndividualImpl::get_chromosome());
    }

private:
    virtual void crossover(IndividualImpl* other) = 0;
    Chromosome* create_cromossome() const override { return new ChromosomeType; }
};
