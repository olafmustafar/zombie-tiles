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
    TileMap(const u_int width, const u_int height);
    void init();
    void print() const;
    Tile *tile(Point coord) const;

private:
    u_int width;
    u_int height;
    QList<Line> walls;
    QList<Tile *> tiles;
};
