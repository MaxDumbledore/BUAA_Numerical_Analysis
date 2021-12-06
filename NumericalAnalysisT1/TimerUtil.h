//
// Created by 40461 on 2021/10/31.
//

#ifndef NUMERICALANALYSIST1_TIMERUTIL_H
#define NUMERICALANALYSIST1_TIMERUTIL_H


#include <chrono>
#include <map>
#include <string>

/**
 * @brief 一个简单的计时器
 * @attention 调用时建议采用字符串字面量作为参数
 */

class TimerUtil {
public:
    static void start(std::string_view name);

    static void finish(std::string_view name);

    static void printAllTime();

    static void clear();

private:
    inline static std::map<std::string_view, std::pair<decltype(std::chrono::system_clock::now()), double>> timer;
};

#endif //NUMERICALANALYSIST1_TIMERUTIL_H
