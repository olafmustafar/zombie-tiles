#pragma once

#include "zombietileschromosome.hpp"
#include <genetic-algorithm/individual.hpp>

class ZombieTilesIndividual : public Individual<ZombieTilesChromosome> {
public:
    void crossover(IndividualImpl* other) override;

private:
    double calculate_fitness() const override;
    TileMap get_map() const;
};
