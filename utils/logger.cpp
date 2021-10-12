#include "logger.hpp"

#include <algorithm>
#include <iostream>

namespace  {
constexpr const char* YELLOW_BEGIN = "\033[1;33m";
constexpr const char* GREEN_BEGIN = "\033[1;32m";
constexpr const char* COLOR_END = "\033[0m";
}

vector<string> Logger::m_operations = {};

void Logger::doing( const char* message ) {
    m_operations.push_back( message );
    cout << GREEN_BEGIN << ident() << message << "..." << COLOR_END << endl;
}

void Logger::doing( const string& message ) {
    doing( message.c_str() );
}

void Logger::doing( const string& message, const function<void()> operation ) {
    Logger::doing( message );
    operation();
    Logger::done();
}

void Logger::done() {
//    cout << GREEN_BEGIN << ident() << m_operations.back() << " DONE!" << COLOR_END << endl;
    m_operations.pop_back();
}

string Logger::ident() {
    ostringstream identation;
    for ( ulong i = 1; i < m_operations.size(); ++i ) {
        identation << "\t";
    }
    return identation.str();
}

void Logger::warn(const char* message)
{
    cout << ident() << ident() << YELLOW_BEGIN << message << COLOR_END << endl;
}

void Logger::warn( const string& message ) {
    cout << ident() << ident() << YELLOW_BEGIN << message << COLOR_END << endl;
}

Logger::log::~log() {
    string str = m_str_stream.str();

    size_t start_pos = 0;
    string from { "\n" };
    string to { "\n\t\t" + ident() };
    while ( ( start_pos = str.find( from, start_pos ) ) != std::string::npos ) {
        str.replace( start_pos, from.length(), to );
        start_pos += to.length();
    }

    cout << ident() << "\t" << str << endl;
}
