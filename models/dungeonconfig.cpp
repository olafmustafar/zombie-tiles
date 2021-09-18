#include "dungeonconfig.hpp"

DungeonConfig *DungeonConfig::m_instance;

DungeonConfig::DungeonConfig(const uint32_t width, const uint32_t height)
    : m_width(width), m_height(height) {}

DungeonConfig &DungeonConfig::get_instance(const uint32_t width,
                                           const uint32_t height) {
    if (!m_instance) {
        m_instance = new DungeonConfig(width, height);
    }

    return *m_instance;
}

DungeonConfig &DungeonConfig::get_instance() {
    if (!m_instance) {
        m_instance = new DungeonConfig();
    }

    return *m_instance;
}

uint32_t DungeonConfig::get_width() const { return m_width; }

void DungeonConfig::set_width(const uint32_t value) { m_width = value; }

uint32_t DungeonConfig::get_height() const { return m_height; }

void DungeonConfig::set_height(const uint32_t value) { m_height = value; }
