#include "dungeonconfig.h"

DungeonConfig *DungeonConfig::m_instance;

DungeonConfig::DungeonConfig(const uint width, const uint height) : width(width), height(height) {}

DungeonConfig &DungeonConfig::get_instance(const uint width, const uint height)
{
    if (!m_instance) {
        m_instance = new DungeonConfig(width, height);
    }

    return *m_instance;
}

DungeonConfig &DungeonConfig::get_instance()
{
    if (!m_instance) {
        m_instance = new DungeonConfig();
    }

    return *m_instance;
}

uint DungeonConfig::get_width() const
{
    return width;
}

void DungeonConfig::set_width(const uint &value)
{
    width = value;
}

uint DungeonConfig::get_height() const
{
    return height;
}

void DungeonConfig::set_height(const uint &value)
{
    height = value;
}
