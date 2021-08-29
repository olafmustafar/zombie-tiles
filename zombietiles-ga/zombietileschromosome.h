#pragma once

#include <vector>
#include <models/tilemap.h>
#include <genetic-algorithm/chromosome.h>
#include "roomgene.h"

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
