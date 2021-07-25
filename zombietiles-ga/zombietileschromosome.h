#pragma once

#include "roomgene.h"
#include <genetic-algorithm/chromosome.h>
#include <vector>

class ZombieTilesChromosome : public Chromosome
{
public:
    ZombieTilesChromosome();
    void randomize() override;
    void mutate() override;
    Chromosome *crossover() const override;

    const std::vector<RoomGene> &get_genes() const;

private:
    std::vector<RoomGene> m_genes;
};
