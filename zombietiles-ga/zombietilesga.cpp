#include "zombietilesga.h"
#include "zombietilesindividualfactory.h"
#include <genetic-algorithm/geneticalgorithm.h>

ZombieTilesGA::ZombieTilesGA(const DungeonConfig *dungeon_config) : dungeon_config(dungeon_config)
{}

void ZombieTilesGA::run()
{
    GeneticAlgorithm ga(new ZombieTilesIndividualFactory, 20);
    ga.init();
    //    for (auto ind : ga.get_population()) {
    //        ind->get_chromosome()->
    //    }
}
