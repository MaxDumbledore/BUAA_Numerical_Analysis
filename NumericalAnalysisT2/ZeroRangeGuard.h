//
// Created by 40461 on 2021/11/16.
//

#ifndef NUMERICALANALYSIST2_ZERORANGEGUARD_H
#define NUMERICALANALYSIST2_ZERORANGEGUARD_H

#include <vector>

/**
 * @brief      һ������epsilon��Χ���ػ���
 * ģ����Python�е�with ...:���
 * һ���������ж���ZeroRangeGuard��ı������µ�epsilon���ᱻ���ã�ֱ���������������Ż�ʧЧ
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