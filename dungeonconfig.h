#pragma once

#include <cstdint>

class DungeonConfig
{
public:
    static DungeonConfig& get_instance(const uint32_t width, const uint32_t height);
    static DungeonConfig& get_instance();

    uint32_t get_width() const;
    void set_width(const uint32_t value);

    uint32_t get_height() const;
    void set_height(const uint32_t value);

private:
    DungeonConfig(const uint32_t width, const uint32_t height);
    DungeonConfig() = default;

    static DungeonConfig* m_instance;
    uint32_t m_width;
    uint32_t m_height;
};

