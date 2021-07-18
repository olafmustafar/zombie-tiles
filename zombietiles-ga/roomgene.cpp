#include "roomgene.h"

#include <utils/randomgenerator.h>

//RoomGene::RoomGene() {}

void RoomGene::randomize()
{
    //    Room(int x, int y, int width, int height, PlacementType placement_type);

    this->room = Room(RandomGenerator::random_between<int>(0, dungeon_config->getWidth()),
                      RandomGenerator::random_between<int>(0, dungeon_config->getHeight()),
                      RandomGenerator::random_between<int>(0, dungeon_config->getWidth()),
                      RandomGenerator::random_between<int>(0, dungeon_config->getHeight()),
                      static_cast<Room::PlacementType>(RandomGenerator::random_between<int>(0, 1)));
}

DungeonConfig *RoomGene::get_dungeon_config() const
{
    return dungeon_config;
}

void RoomGene::set_dungeon_config(DungeonConfig *dungeon_config)
{
    this->dungeon_config = dungeon_config;
}
