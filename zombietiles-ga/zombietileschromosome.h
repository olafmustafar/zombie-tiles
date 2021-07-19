#pragma once

#include "roomgene.h"
#include <dungeonconfig.h>
#include <genetic-algorithm/chromosome.h>
#include <vector>

class ZombieTilesChromosome : public Chromosome
{
public:
    ZombieTilesChromosome();
    void randomize() override;
    void mutate() override;
    Chromosome *crossover() const override;

    DungeonConfig *get_dungeon_config() const;
    void set_dungeon_config(DungeonConfig *dungeon_config);

private:
    DungeonConfig *dungeon_config;
    std::vector<RoomGene> genes;
};
