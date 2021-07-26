#include "zombietilesga.h"
#include "zombietileschromosome.h"
#include "zombietilesindividual.h"
#include "zombietilesindividualfactory.h"
#include <genetic-algorithm/geneticalgorithm.h>
#include <utils/logger.h>

#include <iostream>

namespace {
constexpr int population_size = 20;
}

ZombieTilesGA::ZombieTilesGA(const DungeonConfig *dungeon_config) : dungeon_config(dungeon_config)
{}

void ZombieTilesGA::run()
{
    GeneticAlgorithm<ZombieTilesIndividual> ga(population_size);
    ga.init();

    int index = 0;
    for (Individual *individual : ga.get_population()) {
        std::cout << "individuo: " << index << std::endl;

        const std::vector<RoomGene> genes = static_cast<ZombieTilesChromosome *>(individual->get_chromosome())->get_genes();
        for (const auto &gene : genes) {
            gene.get_room().print();
        }
    }
}
