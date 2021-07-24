#include "zombietilesga.h"
#include "zombietileschromosome.h"
#include "zombietilesindividual.h"
#include "zombietilesindividualfactory.h"
#include <genetic-algorithm/geneticalgorithm.h>
#include <utils/logger.h>

ZombieTilesGA::ZombieTilesGA(const DungeonConfig *dungeon_config) : dungeon_config(dungeon_config)
{}

void ZombieTilesGA::run()
{
    GeneticAlgorithm ga(dungeon_config, new ZombieTilesIndividualFactory, 20);
    ga.init();
    for (auto ind : ga.get_population()) {
        const std::vector<RoomGene> genes
            = static_cast<ZombieTilesChromosome *>(ind->get_chromosome())->get_genes();

        for (const auto &gene : genes) {
            Logger::log(gene.get_room());
        }
    }
}
