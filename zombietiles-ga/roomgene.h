#pragma once

#include "room.h"
#include <dungeonconfig.h>
#include <genetic-algorithm/gene.h>

class RoomGene : public Gene
{
public:
    RoomGene();
    void randomize() override;

    const Room &get_room() const;
    void set_room(const Room &room);

    DungeonConfig *get_dungeon_config() const;
    void set_dungeon_config(DungeonConfig *dungeon_config);

private:
    Room m_room;
};
