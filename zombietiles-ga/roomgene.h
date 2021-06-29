#pragma once

#include "room.h"
#include <genetic-algorithm/gene.h>

class RoomGene : public Gene
{
public:
    void data();
    void randomize();

private:
    Room room;
};
