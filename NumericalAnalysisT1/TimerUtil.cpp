//
// Created by 40461 on 2021/10/31.
//

#include "TimerUtil.h"
#include <iostream>

using namespace std;

void TimerUtil::start(string_view name) {
    timer[name].first = clock();
}

void TimerUtil::finish(string_view name) {
    auto &item = timer[name];
    item.second += (double) (clock() - item.first) / CLOCKS_PER_SEC;
}

double TimerUtil::getElapsedTime(string_view name) {
    return timer[name].second;
}

void TimerUtil::printAllTime() {
    for (auto &[name, item]:timer)
        cout << name << ": " << item.second << endl;
}
