#pragma once

#include <sys/types.h>

class DungeonConfig
{
public:
    static DungeonConfig &get_instance(const u_int width, const u_int height);
    static DungeonConfig &get_instance();

    u_int get_width() const;
    void set_width(const u_int &value);

    u_int get_height() const;
    void set_height(const u_int &value);

private:
    DungeonConfig(const u_int width, const u_int height);
    DungeonConfig() = default;

    static DungeonConfig *instance;
    u_int width;
    u_int height;
};

