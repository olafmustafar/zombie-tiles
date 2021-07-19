#include "roomgene.h"
#include <utils/randomgenerator.h>

RoomGene::RoomGene() : room() {}

void RoomGene::randomize()
{
    int width = RandomGenerator::random_between<int>(1, dungeon_config->get_width());
    int height = RandomGenerator::random_between<int>(1, dungeon_config->get_height());

    this->room = Room(RandomGenerator::random_between<int>(0, dungeon_config->get_width() - width),
                      RandomGenerator::random_between<int>(0, dungeon_config->get_height() - height),
                      width,
                      height,
                      static_cast<Room::PlacementType>(RandomGenerator::random_between<int>(0, 1)));
}

const Room &RoomGene::get_room() const
{
    return room;
}

void RoomGene::set_room(const Room &room)
{
    this->room = room;
}

DungeonConfig *RoomGene::get_dungeon_config() const
{
    return dungeon_config;
}

void RoomGene::set_dungeon_config(DungeonConfig *dungeon_config)
{
    this->dungeon_config = dungeon_config;
}
