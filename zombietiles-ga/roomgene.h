#pragma once

#include "room.h"
#include <dungeonconfig.h>
#include <genetic-algorithm/gene.h>

class RoomGene : public Gene
{
public:
    void data();
    void randomize() override;

    DungeonConfig *get_dungeon_config() const;
    void set_dungeon_config(DungeonConfig *dungeon_config);

private:
    DungeonConfig *dungeon_config;
    Room room;
};
