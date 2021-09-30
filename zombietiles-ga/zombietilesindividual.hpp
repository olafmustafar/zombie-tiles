#pragma once

#include "zombietileschromosome.hpp"
#include <genetic-algorithm/individual.hpp>

class ZombieTilesIndividual : public Individual<ZombieTilesChromosome> {
public:
    double calculate_fitness() const override;
    string to_string();

private:
    TileMap get_map() const;
};
