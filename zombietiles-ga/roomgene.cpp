#include "roomgene.hpp"
#include <utils/randomgenerator.hpp>

RoomGene::RoomGene() : m_room() {}

void RoomGene::randomize()
{
    DungeonConfig dungeon_config = DungeonConfig::get_instance();
    int width = RandomGenerator::random_between<int>(1, dungeon_config.get_width());
    int height = RandomGenerator::random_between<int>(1, dungeon_config.get_height());

    this->m_room = Room(RandomGenerator::random_between<int>(0, dungeon_config.get_width() - width),
                        RandomGenerator::random_between<int>(0, dungeon_config.get_height() - height),
                        width,
                        height,
                        static_cast<Room::PlacementType>(RandomGenerator::random_between<int>(0, 1)));
}

const Room &RoomGene::get_room() const
{
    return m_room;
}

void RoomGene::set_room(const Room &room)
{
    this->m_room = room;
}

string RoomGene::to_string() const
{
    return this->get_room().to_string();
}
