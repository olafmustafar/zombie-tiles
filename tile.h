#pragma once

class Tile
{
public:
    enum class TileType { Floor, Wall };
    Tile(const TileType type);

    TileType get_type() const;
    void set_type(const TileType &value);

private:
    TileType type;
};
