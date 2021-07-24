#include "logger.h"

#include <iostream>

void Logger::log(const Room &room)
{
    std::cout << "room: (" << room.get_width() << "x" << room.get_height() << ")"
              << "[" << room.get_x() << "x" << room.get_y() << "]"
              << static_cast<int>(room.get_placement_type()) << std::endl;
}

void Logger::log(const char *message)
{
    std::cout << message << std::endl;
}

void Logger::doing(const char *message)
{
    std::cout << message << "...";
}

void Logger::done()
{
    std::cout << "DONE!" << std::endl;
}
