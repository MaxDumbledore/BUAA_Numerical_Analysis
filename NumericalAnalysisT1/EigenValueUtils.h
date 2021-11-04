//
// Created by 40461 on 2021/10/30.
//

#ifndef NUMERICALANALYSIST1_EIGENVALUEUTILS_H
#define NUMERICALANALYSIST1_EIGENVALUEUTILS_H

#include "SymBandMatrix.h"
#include <algorithm>

/**
 * @brief 特征值工具类
 * 包含幂法，和反幂法，分别对2-范数和无穷范数进行了实现
 */

class EigenValueUtils {
public:
    static std::pair<double, Vector> powerMethodWithNorm2(const SymBandMatrix &matrix, double eps);

    static std::pair<double, Vector> invPowerMethodWithNorm2(const SymBandMatrix &matrix, double eps);

    static std::pair<double, Vector> powerMethodWithNormInf(const SymBandMatrix &matrix, double eps);

    static std::pair<double, Vector> invPowerMethodWithNormInf(const SymBandMatrix &matrix, double eps);
};


#endif //NUMERICALANALYSIST1_EIGENVALUEUTILS_H
