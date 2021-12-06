//
// Created by 40461 on 2021/11/26.
//

#include <cassert>
#include "NonLinItemMatrix.h"

NonLinItemMatrix::NonLinItemMatrix(int _n) : n(_n), data(n * n) {}

Vector NonLinItemMatrix::operator*(const Vector &v) const {
    assert(v.length() == n);
    Vector res(n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            res.at(i) += at(i, j)(v.at(j));
    return res;
}

NonLinItemMatrix NonLinItemMatrix::derivative() const {
    NonLinItemMatrix res(n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            res.at(i, j) = at(i, j).derivative();
    return res;
}
