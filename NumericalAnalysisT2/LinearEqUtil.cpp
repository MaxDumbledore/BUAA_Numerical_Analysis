//
// Created by 40461 on 2021/11/15.
//

#include "LinearEqUtil.h"
#include "ZeroRangeGuard.h"
#include <algorithm>

using namespace std;

int LinearEqUtil::gaussElimination(Matrix &matA) {
    auto n = matA.size();
    int s = 1, k = 1;
    for (; s <= n; ++s) {
        int pos = k;
        for (int i = k + 1; i <= n; i++)
            if (abs(matA.at(i, s)) > abs(matA.at(pos, s)))
                pos = i;
        if (ZeroRangeGuard::isZero(matA.at(pos, s)))
            continue;
        if (pos != k)
            for (int j = s; j <= n; j++)
                swap(matA.at(k, j), matA.at(pos, j));
        for (int i = k + 1; i <= n; i++) {
            auto m = matA.at(i, s) / matA.at(k, s);
            matA.at(i, s) = 0;
            for (int j = s + 1; j <= n; j++)
                matA.at(i, j) -= m * matA.at(k, j);
        }
        ++k;
    }
    return k - 1;
}

Vector LinearEqUtil::solveHomoLinearEq(const Matrix &matA, double freeVariable) {
    auto n = matA.size();
    Matrix matEliminated = matA;
    auto rank = gaussElimination(matEliminated);
    assert(("The dimension of solution space is greater than one", rank == n - 1));
    Vector res(n);
    for (int k = n - 1, p = n; k > 0; k--) {
        if (!ZeroRangeGuard::isZero(matEliminated.at(k, p)) && p > k && !ZeroRangeGuard::isZero(matEliminated.at(k, p - 1))) {
            res.at(p) = freeVariable;
            --p;
        }
        double t = 0;
        for (int i = p + 1; i <= n; i++)
            t -= matEliminated.at(k, i) * res.at(i);
        res.at(p) = t / matEliminated.at(k, p);
        --p;
    }
    return res;
}