//
// Created by 40461 on 2021/10/30.
//

#include "LinearEqLuSolver.h"
#include <algorithm>

using namespace std;

LinearEqLuSolver::LinearEqLuSolver(const SymBandMatrix &matrix) : l(matrix), u(matrix), n(matrix.size()),
                                                                  s(matrix.width()) {
    for (int i = 1; i <= n; i++)
        l.at(i, i) = 1;
    for (int k = 1; k <= n; k++) {
        for (int j = k; j <= min(k + s, n); j++)
            for (int t = max({1, k - s, j - s}); t <= k - 1; t++)
                u.at(k, j) -= l.at(k, t) * u.at(t, j);
        for (int i = k + 1; i <= min(k + s, n); i++) {
            for (int t = max({1, i - s, k - s}); t <= k - 1; t++)
                l.at(i, k) -= l.at(i, t) * u.at(t, k);
            l.at(i, k) /= u.at(k, k);
        }
    }
}

Vector LinearEqLuSolver::solveEq(const Vector &b) {
    Vector y(b);
    for (int i = 1; i <= n; i++)
        for (int t = max(1, i - s); t <= i - 1; t++)
            y.at(i) -= l.at(i, t) * y.at(t);
    Vector x(y);
    for (int i = n; i > 0; i--) {
        for (int t = i + 1; t <= min(i + s, n); t++)
            x.at(i) -= u.at(i, t) * x.at(t);
        x.at(i) /= u.at(i, i);
    }
    return x;
}

const LeftMatrix &LinearEqLuSolver::getL() const {
    return l;
}

const UpMatrix &LinearEqLuSolver::getU() const {
    return u;
}
