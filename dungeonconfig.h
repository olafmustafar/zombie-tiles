#pragma once

#include <sys/types.h>

class DungeonConfig
{
public:
    DungeonConfig(const u_int width, const u_int height);

    u_int get_width() const;
    void set_width(const u_int &value);

    u_int get_height() const;
    void set_height(const u_int &value);

private:
    u_int width;
    u_int height;
};

