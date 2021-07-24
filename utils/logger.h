#pragma once
#include <zombietiles-ga/room.h>

class Logger
{
public:
    Logger() = delete;
    static void log(const Room &room);
    static void log(const char *message);
    static void doing(const char *message);
    static void done();
};
