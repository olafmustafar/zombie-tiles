#include "zombietileschromosome.h"

#include <dungeonconfig.h>
#include <utils/randomgenerator.h>

ZombieTilesChromosome::ZombieTilesChromosome() : genes()
{
    for (int i = 0; i < 5; ++i) {
        genes.push_back(RoomGene());
    }
}

void ZombieTilesChromosome::randomize()
{
    for (RoomGene &gene : genes) {
        gene.randomize();
    }
}

void ZombieTilesChromosome::mutate() {}

Chromosome *ZombieTilesChromosome::crossover() const
{
    return nullptr;
}

const std::vector<RoomGene> &ZombieTilesChromosome::get_genes() const
{
    return this->genes;
}
