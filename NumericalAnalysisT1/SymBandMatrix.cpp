//
// Created by 40461 on 2021/10/30.
//

#include "SymBandMatrix.h"
#include <cmath>

using namespace std;

SymBandMatrix::SymBandMatrix(int _n, int _width) : n(_n), w(_width), data((_width + 1) * n) {}

SymBandMatrix SymBandMatrix::genDefaultMatrix() {
    constexpr int N = 501;
    constexpr int WIDTH = 2;
    SymBandMatrix matrixA(N, WIDTH);

    for (int i = 1; i <= N; i++) {
        matrixA.at(i, i) = (1.64 - 0.024 * i) * sin(0.2 * i) - 0.64 * exp(0.1 / i);
        if (i < N)
            matrixA.at(i, i + 1) = 0.16;
        if (i + 1 < N)
            matrixA.at(i, i + 2) = -0.064;
    }
    return matrixA;
}

Vector SymBandMatrix::operator*(const Vector &v) const {
    Vector r(v.length());
    for (int i = 1; i <= n; i++) {
        for (int j = max(1, i - w); j <= min(n, i + w); j++)
            r.at(i) += at(i, j) * v.at(j);
    }
    return r;
}

void SymBandMatrix::addConstOnDiagonal(double cv) {
    for (int i = 1; i <= n; i++)
        at(i, i) += cv;
}
