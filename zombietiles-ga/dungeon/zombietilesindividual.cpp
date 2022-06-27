#include "zombietilesindividual.hpp"

#include "zombietileschromosome.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <helpers/dungeonmatrixhelper.hpp>
#include <helpers/graphhelper.hpp>
#include <helpers/roommaphelper.hpp>
#include <iostream>
#include <models/dungeon.hpp>
#include <models/dungeonmatrix.hpp>
#include <models/graph.hpp>
#include <utils/logger.hpp>
#include <utils/randomgenerator.hpp>

void ZombieTilesIndividual::crossover(IndividualImpl* other)
{
    get_chromosome()->crossover(static_cast<ZombieTilesIndividual*>(other)->get_chromosome());
}

void ZombieTilesIndividual::mutate()
{
    get_chromosome()->mutate();
}

string ZombieTilesIndividual::to_string() const
{
    Dungeon tilemap = RoomMapHelper::create_roommap();

    ZombieTilesChromosome* chromosome = get_chromosome();
    const vector<RoomGene>& genes = chromosome->get_genes();

    for (const RoomGene& gene : genes) {
        RoomMapHelper::add_room_to(tilemap, gene.get_room());
    }

    return RoomMapHelper::to_painted_map_string(tilemap);
}

Dungeon ZombieTilesIndividual::get_map() const
{
    Dungeon dungeon = RoomMapHelper::create_roommap();

    const vector<RoomGene>& genes = get_chromosome()->get_genes();
    for (const RoomGene& gene : genes) {
        dungeon.add_room(gene.get_room());
    }

    return dungeon;
}

double ZombieTilesIndividual::calculate_fitness()
{
    using namespace std;
    Dungeon dungeon = get_map();
    m_metadata = RoomMapHelper::calculate_dungeon_metadata(dungeon);

    if (m_metadata.rooms_count == 0  || m_metadata.diameter == 0) {
        return 0;
    }

    double fitness = 0;
    fitness += (m_metadata.exp_degree * m_metadata.rooms_count * log(m_metadata.diameter))
        / (log(M_E + m_metadata.narrow_count) * pow(10.0, m_metadata.tiny_count));

    return fitness;
}

void ZombieTilesIndividual::report() const
{
    Dungeon d = get_map();
    DungeonMetadata dmd = RoomMapHelper::calculate_dungeon_metadata(d);

    std::cout << "rooms_count: " << dmd.rooms_count
              << " | narrow_count: " << dmd.narrow_count
              << " | tiny_count: " << dmd.tiny_count
              << " | diameter: " << dmd.diameter
              << " | average_degree: " << dmd.average_degree
              << " | exp_degree: " << dmd.exp_degree << "\n";
}
