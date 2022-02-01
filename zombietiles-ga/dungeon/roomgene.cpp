#include "roomgene.hpp"
#include <utils/randomgenerator.hpp>

RoomGene::RoomGene() : m_room() {}

void RoomGene::randomize()
{
    DungeonConfig dungeon_config = DungeonConfig::get_instance();
    int width = Random::random_between<int>(1, dungeon_config.get_width());
    int height = Random::random_between<int>(1, dungeon_config.get_height());

    this->m_room = Room(Random::random_between<int>(0, dungeon_config.get_width() - width),
                        Random::random_between<int>(0, dungeon_config.get_height() - height),
                        width,
                        height,
                        static_cast<Room::PlacementType>(Random::random_between<int>(0, 1)));
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
