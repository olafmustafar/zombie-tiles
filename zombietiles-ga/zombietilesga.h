#pragma once

#include <dungeonconfig.h>

class ZombieTilesGA
{
public:
    ZombieTilesGA(const DungeonConfig *dungeon_config);
    void run();

private:
    const DungeonConfig *dungeon_config;
};
