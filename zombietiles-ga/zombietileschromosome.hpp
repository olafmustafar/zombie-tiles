#pragma once

#include "roomgene.hpp"
#include <genetic-algorithm/chromosome.hpp>
#include <models/tilemap.hpp>
#include <vector>

class ZombieTilesChromosome : public Chromosome {
public:
    ZombieTilesChromosome();
    void randomize() override;
    void mutate() override;
    Chromosome* crossover() const override;
    const std::vector<RoomGene>& get_genes() const;

    string to_string() const override;

private:
    std::vector<RoomGene> m_genes;
};
