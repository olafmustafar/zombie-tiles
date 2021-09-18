#pragma once

#include <vector>
#include <models/tilemap.hpp>
#include <genetic-algorithm/chromosome.hpp>
#include "roomgene.hpp"

class ZombieTilesChromosome : public Chromosome
{
public:
    ZombieTilesChromosome();
    void randomize() override;
    void mutate() override;
    Chromosome* crossover() const override;
    const std::vector<RoomGene>& get_genes() const;

    string to_string() const;

private:
    std::vector<RoomGene> m_genes;
    TileMap m_tilemap;

    void corridors_count();
};
