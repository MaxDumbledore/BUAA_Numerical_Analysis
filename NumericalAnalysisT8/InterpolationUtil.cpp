//
// Created by 40461 on 2021/11/28.
//

#include "InterpolationUtil.h"
#include "Matrix.h"
using namespace std;

Vector InterpolationUtil::valueOfLagrangeFunc(double x, const Vector &p) {
    assert(p.length() == 3);
    return {(x - p.at(2)) * (x - p.at(3)) / ((p.at(1) - p.at(2)) * (p.at(1) - p.at(3))),
            (x - p.at(1)) * (x - p.at(3)) / ((p.at(2) - p.at(1)) * (p.at(2) - p.at(3))),
            (x - p.at(1)) * (x - p.at(2)) / ((p.at(3) - p.at(1)) * (p.at(3) - p.at(2)))};
}

double InterpolationUtil::twoDimQuadLagrangeInterpolation(double x, double y, const Vector &p, const Vector &q,
                                                          const Matrix &m) {
    assert(p.length() == q.length() && p.length() == m.size());
    // \sum_{k=1}^3 \sum_{r=1}^3 l_k(x) l'_r(y) f_{x_k,y_r}
    return valueOfLagrangeFunc(x, p).outer(valueOfLagrangeFunc(y, q)).indexMultiply(m).sum();
}
