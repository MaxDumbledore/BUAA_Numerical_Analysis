//
// Created by 40461 on 2021/11/27.
//

#include "NonLinearEqUtil.h"
#include "Matrix.h"
#include "LinearEqUtil.h"
#include "ZeroRangeGuard.h"
#include <iostream>

using namespace std;

Vector NonLinearEqUtil::solveByNewtonMethod(const NonLinItemMatrix &mat, const Vector &c, const Vector &initX) {
    auto n = mat.size();
    Vector x= initX;
    auto dMat = mat.derivative();
    // F(x)函数
    auto f = [&](const Vector &x) -> auto {
        return mat * x - c;
    };

    // F'(x)函数矩阵，矩阵中每一项都是一个函数，F'(x)_{ij}为\partial F_i(x_j) /\partial x_j
    auto fd = [&](const Vector &x) -> auto {
        Matrix r(n);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                r.at(i, j) = dMat.at(i, j)(x.at(j));
        return r;
    };

    Vector deltaX(n);
    // 迭代主循环
    int k = 0;
    do {
        x += deltaX;
        deltaX = LinearEqUtil::solveByGauss(fd(x), {-f(x)}).front();
        ++k;
        assert(("Too many iterations Newton Method!", k < 1000));
    } while (!ZeroRangeGuard::isZero(deltaX.normInf() / x.normInf()));
    //cout << "Newton Method: " << k << " iterations" << endl;
    return x;
}
