#include "zombietileschromosome.h"

#include <dungeonconfig.h>
#include <utils/randomgenerator.h>

ZombieTilesChromosome::ZombieTilesChromosome() : m_genes()
{
    for (int i = 0; i < 5; ++i) {
        m_genes.push_back(RoomGene());
    }
}

void ZombieTilesChromosome::randomize()
{
    for (RoomGene &gene : m_genes) {
        gene.randomize();
    }
}

void ZombieTilesChromosome::mutate()
{
    //    const int size = m_genes.size();
}

Chromosome *ZombieTilesChromosome::crossover() const
{
    return nullptr;
}

const std::vector<RoomGene> &ZombieTilesChromosome::get_genes() const
{
    return m_genes;
}

string ZombieTilesChromosome::to_string() const
{
    string str = "";
    for (const RoomGene& gene : m_genes) {
        str += gene.get_room().to_string() + '\n';
    }
    return str;
}
