#include "zombietileschromosome.h"

#include <utils/randomgenerator.h>

ZombieTilesChromosome::ZombieTilesChromosome() : genes()
{
    for (int i = 0; i < 5; ++i) {
        RoomGene roomGene;
        roomGene.set_dungeon_config(this->dungeon_config);
        genes.push_back(roomGene);
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

DungeonConfig *ZombieTilesChromosome::get_dungeon_config() const
{
    return dungeon_config;
}

void ZombieTilesChromosome::set_dungeon_config(DungeonConfig *dungeon_config)
{
    this->dungeon_config = dungeon_config;
}

const std::vector<RoomGene> &ZombieTilesChromosome::get_genes() const
{
    return this->genes;
}
