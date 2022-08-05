#include "dungeonconfig.hpp"

DungeonConfig* DungeonConfig::m_instance;

DungeonConfig::DungeonConfig()
    : DungeonConfig { 10, 10 }
{
}

DungeonConfig::DungeonConfig(const uint32_t width, const uint32_t height)
    : width(width)
    , height(height)
    , number_of_iterations(300)
    , iterations_without_change_limit { 50 }
{
}

DungeonConfig& DungeonConfig::get_instance(const uint32_t width, const uint32_t height)
{
    if (!m_instance) {
        m_instance = new DungeonConfig(width, height);
    }

    return *m_instance;
}

DungeonConfig& DungeonConfig::get_instance()
{
    if (!m_instance) {
        m_instance = new DungeonConfig();
    }

    return *m_instance;
}

uint32_t DungeonConfig::get_width() const { return width; }

void DungeonConfig::set_width(const uint32_t value) { width = value; }

uint32_t DungeonConfig::get_height() const { return height; }

void DungeonConfig::set_height(const uint32_t value) { height = value; }

uint32_t DungeonConfig::get_rooms_count() const { return rooms_count; }

uint32_t DungeonConfig::get_population_size() const { return population_size; }

void DungeonConfig::set_population_size(uint32_t new_population_size) { population_size = new_population_size; }

void DungeonConfig::set_rooms_count(uint32_t new_rooms_count) { rooms_count = new_rooms_count; }
