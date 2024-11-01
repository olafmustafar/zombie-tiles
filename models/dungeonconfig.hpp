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

    uint32_t get_population_size() const;
    void set_population_size(uint32_t population_size);

    uint32_t get_rooms_count() const;
    void set_rooms_count(uint32_t rooms_count);

    uint32_t width;
    uint32_t height;
    uint32_t rooms_count;
    uint32_t number_of_iterations;
    uint32_t population_size;
    uint32_t iterations_without_change_limit;

private:
    DungeonConfig(const uint32_t width, const uint32_t height);
    DungeonConfig();

    static DungeonConfig* m_instance;
};

