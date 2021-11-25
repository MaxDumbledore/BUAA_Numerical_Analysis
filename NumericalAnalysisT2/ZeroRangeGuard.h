//
// Created by 40461 on 2021/11/16.
//

#ifndef NUMERICALANALYSIST2_ZERORANGEGUARD_H
#define NUMERICALANALYSIST2_ZERORANGEGUARD_H

#include <vector>

/**
 * @brief      一个控制epsilon范围的守护类
 * 模仿了Python中的with ...:语句
 * 一个作用域中定义ZeroRangeGuard类的变量，新的epsilon将会被设置，直到这个作用域结束才会失效
 */

class ZeroRangeGuard {
public:
    explicit ZeroRangeGuard(double range) {
        rangeList.emplace_back(range);
    }

    ~ZeroRangeGuard() {
        rangeList.pop_back();
    }

    inline static bool isZero(double value) {
        double &z = rangeList.back();
        return value <= z && value >= -z;
    }

    inline static const std::vector<double> &getRangeList() {
        return rangeList;
    }

private:
    inline static std::vector<double> rangeList{1E-15};
};

#endif //NUMERICALANALYSIST2_ZERORANGEGUARD_H