#include "tile.h"

Tile::Tile(const TileType type) : type(type) {}

Tile::TileType Tile::get_type() const
{
    return type;
}

void Tile::set_type(const TileType &value)
{
    type = value;
}
