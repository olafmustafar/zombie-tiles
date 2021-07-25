#pragma once

#include <sys/types.h>

class DungeonConfig
{
public:
    static DungeonConfig &get_instance(const uint width, const uint height);
    static DungeonConfig &get_instance();

    uint get_width() const;
    void set_width(const uint &value);

    uint get_height() const;
    void set_height(const uint &value);

private:
    DungeonConfig(const uint width, const uint height);
    DungeonConfig() = default;

    static DungeonConfig *m_instance;
    uint width;
    uint height;
};

