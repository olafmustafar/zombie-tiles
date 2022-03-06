#pragma once

#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


class Logger {
public:
    struct log {
        ~log();

        template <class T>
        log& operator<<(const T& message)
        {
            m_str_stream << message;
            return *this;
        }

    private:
        std::ostringstream m_str_stream;
    };

    Logger() = delete;

    static void doing(const char* message);
    static void doing(const std::string& message);
    static void doing(const std::string& message, const std::function<void()> operation);
    static void done();
    static void warn(const char* message);
    static void warn(const std::string& message);
    static void setLoggin(bool log);

private:
    static std::vector<std::string> m_operations;
    static bool m_log;

    static std::string ident();
};
