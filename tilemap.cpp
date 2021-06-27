#include "tilemap.h"

#include <iostream>

TileMap::TileMap(const u_int width, const u_int height)
    : width(width), height(height), walls({}), tiles({})
{}

void TileMap::init()
{
    for (u_int i = 0; i < this->width; i++) {
        for (u_int j = 0; j < this->height; j++) {
            tiles.append(new Tile(Tile::TileType::Floor));
        }
    }
}

void TileMap::print() const
{
    for (u_int j = 0; j < this->height; j++) {
        for (u_int i = 0; i < this->width; i++) {
            std::cout << QString("[%0]").arg(static_cast<int>(tiles[i]->get_type())).toStdString();
        }
        std::cout << std::endl;
    }
}

Tile *TileMap::tile(Point coord) const
{
    return this->tiles[(this->width * coord.y) + coord.x];
}
