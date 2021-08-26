#pragma once

#include <models/room.h>
#include <dungeonconfig.h>

class RoomGene
{
public:
    RoomGene();
    void randomize();

    const Room& get_room() const;
    void set_room(const Room& room);

    string to_string() const;

private:
    Room m_room;
};
