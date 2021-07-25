#pragma once

#include "tile.h"
#include <QList>

struct Point
{
    int x;
    int y;
};

struct Line
{
    Point start;
    Point end;
};

class TileMap
{
public:
    TileMap(const uint width, const uint height);
    void init();
    void print() const;
    Tile *tile(Point coord) const;

private:
    uint width;
    uint height;
    QList<Line> walls;
    QList<Tile *> tiles;
};
