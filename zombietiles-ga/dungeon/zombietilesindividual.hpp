#pragma once

#include "zombietileschromosome.hpp"
#include <genetic-algorithm/individual.hpp>

class ZombieTilesIndividual : public Individual<ZombieTilesChromosome> {
public:
    void crossover(IndividualImpl* other) override;
    void mutate() override;
    string to_string() const override;
    Dungeon get_map() const;

private:
    double calculate_fitness() const override;
};
