//
// Created by 40461 on 2021/11/28.
//

#include "NonSqMatrix.h"
#include <cassert>
#include "Matrix.h"

NonSqMatrix::NonSqMatrix(int _m, int _n) : m(_m), n(_n), data(m * n) {}

NonSqMatrix NonSqMatrix::operator*(const NonSqMatrix &other) const {
    assert(n == other.m);
    NonSqMatrix result(m, other.n);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= other.n; j++)
            for (int k = 1; k <= n; k++)
                result.at(i, j) += at(i, k) * other.at(k, j);
    return result;
}

Matrix NonSqMatrix::toMatrix() const &{
    assert(m == n);
    Matrix result(m);
    result.data = data;
    return result;
}

Matrix NonSqMatrix::toMatrix() &&{
    assert(m == n);
    Matrix result(0);
    result.data = std::move(data);
    result.n = m;
    return result;
}

NonSqMatrix NonSqMatrix::transpose() const {
    NonSqMatrix mat(n, m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            mat.at(i, j) = at(j, i);
    return mat;
}