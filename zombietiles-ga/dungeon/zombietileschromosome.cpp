#include "zombietileschromosome.hpp"

#include <algorithm>
#include <models/dungeonconfig.hpp>
#include <utils/randomgenerator.hpp>

using namespace std;

ZombieTilesChromosome::ZombieTilesChromosome()
    : m_genes()
{
    for (uint32_t i = 0; i < DungeonConfig::get_instance().get_rooms_count(); ++i) {
        m_genes.push_back(RoomGene());
    }
}

void ZombieTilesChromosome::randomize()
{
    for (RoomGene& gene : m_genes) {
        gene.randomize();
    }
}

void ZombieTilesChromosome::mutate()
{
    for (auto i = 0; i < (m_genes.size() * 0.2); i++) {
        size_t index = Random::random_between<size_t>(0, m_genes.size() - 1);
        m_genes[index].randomize();
    }
}

void ZombieTilesChromosome::crossover(Chromosome* other)
{
    ZombieTilesChromosome* other_ = static_cast<ZombieTilesChromosome*>(other);
    for (int i = 0; i < 3; ++i) {
        if (i % 2 == 0) {
            swap(m_genes[i], other_->m_genes[i]);
        }
    }

    for (size_t i = 3; i < m_genes.size(); ++i) {
        double swap_c = Random::random_between(0.0, 1.0);
        if (swap_c < 0.5) {
            swap(m_genes[i], other_->m_genes[i]);
        }
    }
}

const std::vector<RoomGene>& ZombieTilesChromosome::get_genes() const
{
    return m_genes;
}

string ZombieTilesChromosome::to_string() const
{
    string str = "chromosome( ";
    for (const RoomGene& gene : m_genes) {
        str += '\n' + gene.get_room().to_string();
    }
    str += " )";
    return str;
}
