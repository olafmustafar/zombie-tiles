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

    uint32_t get_generations() const;
    void set_generations(uint32_t generations);

    uint32_t get_population_size() const;
    void set_population_size(uint32_t population_size);

    uint32_t get_rooms_count() const;
    void set_rooms_count(uint32_t rooms_count);

private:
    DungeonConfig(const uint32_t width, const uint32_t height);
    DungeonConfig() = default;

    static DungeonConfig* m_instance;
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_rooms_count;
    uint32_t m_generations;
    uint32_t m_population_size;
};

