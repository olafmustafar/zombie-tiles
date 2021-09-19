#include "zombietilesindividual.hpp"

#include "zombietileschromosome.hpp"
#include <algorithm>
#include <cstdint>
#include <helpers/tilemaphelper.hpp>
#include <models/tilemap.hpp>
#include <utils/logger.hpp>

double ZombieTilesIndividual::evaluate() const
{
    double value = 0.00;

    TileMap tilemap = TileMapHelper::create_tilemap();

    ZombieTilesChromosome* chromosome = get_chromosome();
    const vector<RoomGene>& genes = chromosome->get_genes();

    for (const RoomGene& gene : genes) {
        tilemap.addRoom(gene.get_room());
    }

    if (tilemap.get_rooms().size() != TileMapHelper::rooms_count_of(tilemap)) {
        //Comparando o tamanho das salas inseridas com o contador das salas
        Logger::warn(string("tamanho espearado: ") + std::to_string(TileMapHelper::rooms_count_of(tilemap)));
        Logger::warn(string("tamanho obtido: ") + std::to_string(tilemap.get_rooms().size()));
        Logger::warn(chromosome->to_string());
        Logger::warn(tilemap.to_string());
    }

    // const double n_rooms = map.get_rooms().size();
    // const double diameter = ,
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