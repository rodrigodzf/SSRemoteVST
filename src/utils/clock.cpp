//Own Libs
#include <src/utils/clock.h>

//C++ Libs
#include <chrono>
#include <sstream>
#include <iostream>
#include <bits/unique_ptr.h>
#include <iomanip>

std::string SSR::compute_current_time()
{
    std::time_t now_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    struct tm* parts = std::localtime(&now_c);

    std::unique_ptr<std::stringstream> ss(new std::stringstream(std::string("")));

    int year    = 1900 + parts->tm_year;
    int month   = 1    + parts->tm_mon;
    int day     = parts->tm_mday;
    int hour    = parts->tm_hour;
    int min     = parts->tm_min;
    int sec     = parts->tm_sec;

    *ss << year                 << "-";
    *ss << std::setfill('0')    << std::setw(2);
    *ss << month                << "-";
    *ss << std::setfill('0')    << std::setw(2);
    *ss << day << " ";
    *ss << std::setfill('0')    << std::setw(2);
    *ss << hour                 << ":";
    *ss << std::setfill('0')    << std::setw(2);
    *ss << min                  << ":";
    *ss << std::setfill('0')    << std::setw(2);
    *ss << sec;

    return ss->str();
}