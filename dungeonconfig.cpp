#include "dungeonconfig.h"

DungeonConfig::DungeonConfig(const u_int width, const u_int height)
    : width(width), height(height)
{}

u_int DungeonConfig::getWidth() const
{
    return width;
}

void DungeonConfig::setWidth(const u_int &value)
{
    width = value;
}

u_int DungeonConfig::getHeight() const
{
    return height;
}

void DungeonConfig::setHeight(const u_int &value)
{
    height = value;
}
