#include "dungeonconfig.h"

DungeonConfig::DungeonConfig(const u_int width, const u_int height)
    : width(width), height(height)
{}

u_int DungeonConfig::get_width() const
{
    return width;
}

void DungeonConfig::set_width(const u_int &value)
{
    width = value;
}

u_int DungeonConfig::get_height() const
{
    return height;
}

void DungeonConfig::set_height(const u_int &value)
{
    height = value;
}
