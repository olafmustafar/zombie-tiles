#include "dungeonconfig.hpp"

DungeonConfig *DungeonConfig::m_instance;

DungeonConfig::DungeonConfig(const uint32_t width, const uint32_t height)
    : m_width(width)
    , m_height(height)
{
}

DungeonConfig& DungeonConfig::get_instance(const uint32_t width,

    const uint32_t height)
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

uint32_t DungeonConfig::get_width() const { return m_width; }

void DungeonConfig::set_width(const uint32_t value) { m_width = value; }

uint32_t DungeonConfig::get_height() const { return m_height; }

void DungeonConfig::set_height(const uint32_t value) { m_height = value; }

uint32_t DungeonConfig::get_rooms_count() const { return m_rooms_count; }

uint32_t DungeonConfig::get_generations() const { return m_generations; }

void DungeonConfig::set_generations(uint32_t generations) { m_generations = generations; }

uint32_t DungeonConfig::get_population_size() const { return m_population_size; }

void DungeonConfig::set_population_size(uint32_t population_size) { m_population_size = population_size; }

void DungeonConfig::set_rooms_count(uint32_t rooms_count) { m_rooms_count = rooms_count; }
