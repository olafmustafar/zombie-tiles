#include "zombietilesindividual.h"

#include "zombietileschromosome.h"

#include <dungeonconfig.h>
#include <utils/randomgenerator.h>
#include <models/tilemap.h>

double ZombieTilesIndividual::evaluate() const
{   
    ZombieTilesChromosome* chromosome = get_chromosome();
    DungeonConfig dungeon = DungeonConfig::get_instance();

    TileMap tilemap(dungeon.get_width(), dungeon.get_height());

    for (RoomGene room_gene : chromosome->get_genes()) {
        room_gene.get_room();
    }

    return 0.00;
}

string ZombieTilesIndividual::to_string()
{
    return Individual<ZombieTilesChromosome>::get_chromosome()->to_string();
}
