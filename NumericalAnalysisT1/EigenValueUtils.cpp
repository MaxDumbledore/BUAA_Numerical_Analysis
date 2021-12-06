//
// Created by 40461 on 2021/10/30.
//

#include "EigenValueUtils.h"
#include "LinearEqLuSolver.h"
#include <iostream>
#include "TimerUtil.h"

using namespace std;

pair<double, Vector> EigenValueUtils::powerMethodWithNorm2(const SymBandMatrix &matrix, const double eps) {
    TimerUtil::start(__func__);
    Vector u(matrix.size(), true), y;
    double beta = 0, oldBeta;
    int epochs = 0;
    do {
        oldBeta = beta;
        auto eta = u.norm2();
        y = u / eta;
        u = matrix * y;
        beta = y.dot(u);
        ++epochs;
#ifndef NDEBUG
        //cout << ++epochs << ":" << beta << endl;
#endif
    } while (eps <= abs((beta - oldBeta) / beta));
#ifndef NDEBUG
    cout << epochs << endl;
#endif
    TimerUtil::finish(__func__);
    return {beta, move(y)};
}

pair<double, Vector> EigenValueUtils::invPowerMethodWithNorm2(const SymBandMatrix &matrix, const double eps) {
    TimerUtil::start(__func__);
    Vector u(matrix.size(), true), y;
    LinearEqLuSolver solver(matrix);
    double beta = 0, oldBeta;
    int epochs = 0;
    do {
        oldBeta = beta;
        auto eta = u.norm2();
        y = u / eta;
        u = solver.solveEq(y);
        beta = y.dot(u);
        ++epochs;
#ifndef NDEBUG
        //cout << ++epochs << ":" << beta << endl;
#endif
    } while (eps <= abs((beta - oldBeta) / beta));
#ifndef NDEBUG
    cout << epochs << endl;
#endif
    TimerUtil::finish(__func__);
    return {1 / beta, move(y)};
}

pair<double, Vector> EigenValueUtils::powerMethodWithNormInf(const SymBandMatrix &matrix, const double eps) {
    TimerUtil::start(__func__);
    Vector u(matrix.size(), true), y;
    double beta = 0, oldBeta;
    bool prevHSign;
    int r = u.maxNormElement();
    int epochs = 0;
    do {
        oldBeta = beta;
        prevHSign = u.at(r) < 0;
        y = u / abs(u.at(r));
        u = matrix * y;
        r = u.maxNormElement();
        beta = prevHSign ? -u.at(r) : u.at(r);
        ++epochs;
    } while (eps <= abs((beta - oldBeta) / beta));
#ifndef NDEBUG
    cout << epochs << endl;
#endif
    TimerUtil::finish(__func__);
    return {beta, move(y)};
}

pair<double, Vector> EigenValueUtils::invPowerMethodWithNormInf(const SymBandMatrix &matrix, const double eps) {
    TimerUtil::start(__func__);
    Vector u(matrix.size(), true), y;
    double beta = 0, oldBeta;
    bool prevHSign;
    int r = u.maxNormElement();
    int epochs = 0;
    LinearEqLuSolver solver(matrix);
    do {
        oldBeta = beta;
        prevHSign = u.at(r) < 0;
        y = u / abs(u.at(r));
        u = solver.solveEq(y);
        r = u.maxNormElement();
        beta = prevHSign ? -u.at(r) : u.at(r);
        ++epochs;
    } while (eps <= abs((beta - oldBeta) / beta));
#ifndef NDEBUG
    cout << epochs << endl;
#endif
    TimerUtil::finish(__func__);
    return {1 / beta, move(y)};
}
