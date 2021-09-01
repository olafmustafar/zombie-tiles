#include "zombietilesindividual.h"

#include "zombietileschromosome.h"

#include <cstdint>
#include <models/dungeonconfig.h>
#include <models/tilemap.h>
#include <utils/randomgenerator.h>

double ZombieTilesIndividual::evaluate() const
{
    double value = 0.00;

    TileMap map = get_map();
    // const double n_rooms = map.get_rooms().size();
    // const double n_narrow = count_narrow_rooms(map);
    // const double n_tiny = count_tiny_rooms(map);
    
        // for (uint32_t i = 0; i < map.get_width(); ++i) {
        //     for (uint32_t j = 0; j < map.get_height(); ++j) {
        //         if (map[i][j] == TileMap::EMPTY_ROOM) {
        //             continue;
        //         }

        //         if( i != (map.get_width() + 1)){

        //         }
        //     }
        // }

        return 0.00;
}

string ZombieTilesIndividual::to_string()
{
    return Individual<ZombieTilesChromosome>::get_chromosome()->to_string();
}

TileMap ZombieTilesIndividual::get_map() const
{
    const ZombieTilesChromosome* chromosome = get_chromosome();
    const DungeonConfig dungeon = DungeonConfig::get_instance();

    TileMap tilemap(dungeon.get_width(), dungeon.get_height());
    for (RoomGene room_gene : chromosome->get_genes()) {
        tilemap.addRoom(room_gene.get_room());
    }
    return tilemap;
}

// double ZombieTilesIndividual::count_narrow_rooms(const TileMap& map) const
// {
//     double count = 0.00;

//     for (const Room& room : map.get_rooms()) {
//         if (room.get_width() == 1 && room.get_height() != 1
//             || room.get_width() != 1 && room.get_height() == 1) {
//             count += 1.00;
//         }
//     }

//     return count;
// }

// double ZombieTilesIndividual::count_tiny_rooms(const TileMap& map) const
// {
//     double count = 0.00;

//     for (const Room& room : map.get_rooms()) {
//         if (room.get_width() == 1 && room.get_height() == 1) {
//             count += 1.00;
//         }
//     }

//     return count;
// }

// void ZombieTilesIndividual::get_graph(const TileMap& map) const
// {
//     for (uint32_t i = 0; i < map.get_width(); ++i) {
//         for (uint32_t j = 0; j < map.get_height(); ++j) {
//             if( i)

//         }
//     }
// }