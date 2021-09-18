#include "zombietileschromosome.hpp"

#include <models/dungeonconfig.hpp>
#include <utils/randomgenerator.hpp>

ZombieTilesChromosome::ZombieTilesChromosome()
    : m_genes(),
      m_tilemap(
              DungeonConfig::get_instance().get_width(), DungeonConfig::get_instance().get_height())
{
    for (int i = 0; i < 5; ++i) {
        m_genes.push_back(RoomGene());
    }
}

void ZombieTilesChromosome::randomize()
{
    for (RoomGene &gene : m_genes) {
        gene.randomize();
        m_tilemap.addRoom(gene.get_room());
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

    str += m_tilemap.to_string();

    return str;
}
