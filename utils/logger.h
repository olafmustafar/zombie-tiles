#pragma once

class Logger
{
public:
    Logger() = delete;
    static void log(const char *message);
    static void doing(const char *message);
    static void done();
};
