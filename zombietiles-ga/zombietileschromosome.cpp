#include "zombietileschromosome.hpp"

#include <algorithm>
#include <models/dungeonconfig.hpp>
#include <utils/randomgenerator.hpp>

using namespace std;

ZombieTilesChromosome::ZombieTilesChromosome()
    : m_genes()
{
    for (int i = 0; i < 5; ++i) {
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
    //    const int size = m_genes.size();
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
        double swap_c = RandomGenerator::random_between(0.0, 1.0);
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
