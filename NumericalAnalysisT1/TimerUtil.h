//
// Created by 40461 on 2021/10/31.
//

#ifndef NUMERICALANALYSIST1_TIMERUTIL_H
#define NUMERICALANALYSIST1_TIMERUTIL_H


#include <ctime>
#include <map>
#include <string>

class TimerUtil {
public:
    static void start(std::string_view name);

    static void finish(std::string_view name);

    static double getElapsedTime(std::string_view name);

    static void printAllTime();

private:
    inline static std::map<std::string_view, std::pair<clock_t, double>> timer;
};

#endif //NUMERICALANALYSIST1_TIMERUTIL_H
