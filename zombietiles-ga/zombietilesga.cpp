#include "zombietilesga.h"
#include "zombietileschromosome.h"
#include "zombietilesindividual.h"
#include "zombietilesindividualfactory.h"
#include <genetic-algorithm/geneticalgorithm.h>
#include <utils/logger.h>
#include <utils/randomgenerator.h>

#include <iostream>

namespace {
constexpr int POPULATION_SIZE = 20;
}

void ZombieTilesGA::run()
{
    GeneticAlgorithm<ZombieTilesIndividual> ga(POPULATION_SIZE);
    ga.init();

    //    std::list<int>

    //    int index = 0;
    //    for (Individual *individual : ga.get_population()) {
    //        std::cout << "individuo: " << index << std::endl;

    //        const std::vector<RoomGene> genes = static_cast<ZombieTilesChromosome
    //        *>(individual->get_chromosome())->get_genes(); for (const auto &gene : genes) {
    //            gene.get_room().print();
    //        }
    //    }
}
