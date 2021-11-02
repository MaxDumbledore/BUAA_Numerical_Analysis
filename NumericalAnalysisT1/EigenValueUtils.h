//
// Created by 40461 on 2021/10/30.
//

#ifndef NUMERICALANALYSIST1_EIGENVALUEUTILS_H
#define NUMERICALANALYSIST1_EIGENVALUEUTILS_H

#include "SymBandMatrix.h"
#include <algorithm>

class EigenValueUtils {
public:
    static std::pair<double, Vector> powerMethodWithNorm2(const SymBandMatrix &matrix, double eps = 1e-12);

    static std::pair<double, Vector> invPowerMethodWithNorm2(const SymBandMatrix &matrix, double eps = 1e-12);

    static std::pair<double, Vector> powerMethodWithNormInf(const SymBandMatrix &matrix, double eps=1e-12);

    static std::pair<double, Vector> invPowerMethodWithNormInf(const SymBandMatrix &matrix, double eps=1e-12);
};


#endif //NUMERICALANALYSIST1_EIGENVALUEUTILS_H
