//
// Created by 40461 on 2021/10/31.
//

#include "TimerUtil.h"
#include <iostream>

using namespace std;
using namespace chrono;

void TimerUtil::start(string_view name) {
    timer[name].first = system_clock::now();
}

void TimerUtil::finish(string_view name) {
    auto &item = timer[name];
    item.second += (double) duration_cast<microseconds>(system_clock::now() - item.first).count();
}

void TimerUtil::printAllTime() {
    for (auto &[name, item]:timer)
        cout << name << ": " << item.second * microseconds::period::num / microseconds::period::den << endl;
}

void TimerUtil::clear() {
    timer.clear();
}
