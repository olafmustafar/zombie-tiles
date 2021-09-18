#include "logger.hpp"

#include <iostream>

vector<string> Logger::m_operations = {};

void Logger::log(const char* message)
{
    cout << ident() << message << endl;
}

void Logger::doing(const char* message)
{
    m_operations.push_back(message);
    cout << ident() << message << "..." << endl;
}

void Logger::doing(const string& message)
{
    doing(message.c_str());
}

void Logger::doing(const string& message, const function<void()> operation)
{
    Logger::doing(message);
    operation();
    Logger::done();
}

void Logger::done()
{
    cout << ident() << m_operations.back() << " DONE!" << endl;
    m_operations.pop_back();
}

string Logger::ident()
{
    string identation = "";
    for (ulong i = 1; i < m_operations.size(); ++i) {
        cout << "\t";
    }
    return identation;
}

void Logger::warn(const char* message)
{
    cout << ident() << "\033[1;4;33m" << message << "\033[0m\n" << endl;
}

void Logger::warn(const string& message)
{
    cout << ident() << "\033[1;4;33m" << message << "\033[0m\n" << endl;
}