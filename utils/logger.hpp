#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class Logger
{
public:
    Logger() = delete;

    static void log(const char* message);
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
