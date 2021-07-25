#include "tilemap.h"

#include <iostream>

TileMap::TileMap(const uint width, const uint height)
    : width(width), height(height), walls({}), tiles({})
{}

void TileMap::init()
{
    for (uint i = 0; i < this->width; i++) {
        for (uint j = 0; j < this->height; j++) {
            tiles.append(new Tile(Tile::TileType::Floor));
        }
    }
}

void TileMap::print() const
{
    for (uint j = 0; j < this->height; j++) {
        for (uint i = 0; i < this->width; i++) {
            std::cout << QString("[%0]").arg(static_cast<int>(tiles[i]->get_type())).toStdString();
        }
        std::cout << std::endl;
    }
}

Tile *TileMap::tile(Point coord) const
{
    return this->tiles[(this->width * coord.y) + coord.x];
}
