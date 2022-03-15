#include "zombietilesindividual.hpp"

#include "zombietileschromosome.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <helpers/dungeonmatrixhelper.hpp>
#include <helpers/graphhelper.hpp>
#include <helpers/roommaphelper.hpp>
#include <models/dungeonmatrix.hpp>
#include <models/graph.hpp>
#include <models/roommap.hpp>
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
    RoomMap tilemap = RoomMapHelper::create_roommap();

    ZombieTilesChromosome* chromosome = get_chromosome();
    const vector<RoomGene>& genes = chromosome->get_genes();

    for (const RoomGene& gene : genes) {
        RoomMapHelper::add_room_to(tilemap, gene.get_room());
    }

    return RoomMapHelper::to_painted_map_string(tilemap);
}

RoomMap ZombieTilesIndividual::get_map() const
{
    RoomMap tilemap = RoomMapHelper::create_roommap();

    ZombieTilesChromosome* chromosome = get_chromosome();
    const vector<RoomGene>& genes = chromosome->get_genes();

    for (const RoomGene& gene : genes) {
        RoomMapHelper::add_room_to(tilemap, gene.get_room());
    }

    return tilemap;
}

double ZombieTilesIndividual::calculate_fitness() const
{
    using namespace std;
    RoomMap tilemap = RoomMapHelper::create_roommap();

    ZombieTilesChromosome* chromosome = get_chromosome();

    const vector<RoomGene>& genes = chromosome->get_genes();

    for (const RoomGene& gene : genes) {
        tilemap.add_room(gene.get_room());
    }

    DungeonMatrix dm = RoomMapHelper::generate_dungeon_matrix(tilemap);

    Graph graph = RoomMapHelper::to_graph(dm);
    const double n_rooms = static_cast<double>(DungeonMatrixHelper::rooms_count_of(dm));
    const double n_narrow = static_cast<double>(DungeonMatrixHelper::narrow_rooms_of(dm));
    const double n_tiny = static_cast<double>(DungeonMatrixHelper::tiny_rooms_of(dm));

    const double diameter = GraphHelper::diameter_of(graph);
    const double average_degree = GraphHelper::average_degree_of(graph);

    const double exp_degree = pow(M_E, -(pow(average_degree - 2, 2.00)));

    double fitness = 0;
    fitness += (exp_degree * n_rooms * log(diameter))
        / (log(M_E + n_narrow) * pow(10.0, n_tiny));

    return fitness;
}
