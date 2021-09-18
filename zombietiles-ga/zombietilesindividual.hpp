#pragma once

#include "zombietileschromosome.hpp"
#include <genetic-algorithm/individual.hpp>

class ZombieTilesIndividual : public Individual<ZombieTilesChromosome> {
public:
    double evaluate() const override;
    string to_string();

private:
    TileMap get_map() const;
    // void get_graph(const TileMap& map) const; 
    // double count_narrow_rooms(const TileMap& map) const;
    // double count_tiny_rooms(const TileMap& map) const;

};
