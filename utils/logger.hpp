#pragma once

#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

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
        ostringstream m_str_stream;
    };

    Logger() = delete;

    static void doing(const char* message);
    static void doing(const string& message);
    static void doing(const string& message, const function<void()> operation);
    static void done();
    static void warn(const char* message);
    static void warn(const string& message);

private:
    static vector<string> m_operations;
    static string ident();
};
