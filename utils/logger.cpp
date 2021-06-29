#include "logger.h"

#include <iostream>

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
