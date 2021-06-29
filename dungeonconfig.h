#pragma once

#include <sys/types.h>

class DungeonConfig
{
public:
    DungeonConfig(const u_int width, const u_int height);

    u_int getWidth() const;
    void setWidth(const u_int &value);

    u_int getHeight() const;
    void setHeight(const u_int &value);

private:
    u_int width;
    u_int height;
};

