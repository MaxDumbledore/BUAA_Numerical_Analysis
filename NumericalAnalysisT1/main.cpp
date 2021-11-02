#include <iostream>
#include <iomanip>
#include "SymBandMatrix.h"
#include "EigenValueUtils.h"
#include "LinearEqLuSolver.h"
#include "TimerUtil.h"

using namespace std;

void customPrint(double arg) {
    auto old = cout.flags();
    auto exp = (arg == 0) ? 0 : 1 + (int) floor(log10(fabs(arg)));
    auto base = arg * pow(10, -exp);
    cout << fixed << setprecision(12) << base;
    cout << "E" << (exp >= 0 ? '+' : '-') << setw(2) << setfill('0') << abs(exp) << endl;
    cout.flags(old);
}

void solve1() {
    auto matrix = SymBandMatrix::genDefaultMatrix();
    TimerUtil::start(__func__);
    auto lambda1 = EigenValueUtils::powerMethodWithNorm2(matrix).first;
    customPrint(lambda1);

    matrix.addConstOnDiagonal(-lambda1);
    auto lambda501 = EigenValueUtils::powerMethodWithNorm2(matrix).first + lambda1;
    customPrint(lambda501);
    matrix.addConstOnDiagonal(lambda1);

    auto lambdaS = EigenValueUtils::invPowerMethodWithNorm2(matrix).first;
    customPrint(lambdaS);

    for (int k = 1; k < 40; k++) {
        auto mu = lambda1 + k * (lambda501 - lambda1) / 40;
        matrix.addConstOnDiagonal(-mu);
        auto lambda = EigenValueUtils::invPowerMethodWithNorm2(matrix).first + mu;
        customPrint(lambda);
        matrix.addConstOnDiagonal(mu);
    }

    TimerUtil::finish(__func__);

    auto cond2 = abs(lambda1 / lambdaS);
    customPrint(cond2);

    LinearEqLuSolver solver(matrix);

    double det = 1;
    for (int i = 1; i <= matrix.size(); i++)
        det *= solver.getU().at(i, i);
    customPrint(det);
}

void solve2() {
    auto matrix = SymBandMatrix::genDefaultMatrix();
    TimerUtil::start(__func__);
    auto lambda1 = EigenValueUtils::powerMethodWithNormInf(matrix).first;
    customPrint(lambda1);

    matrix.addConstOnDiagonal(-lambda1);
    auto lambda501 = EigenValueUtils::powerMethodWithNormInf(matrix).first + lambda1;
    customPrint(lambda501);
    matrix.addConstOnDiagonal(lambda1);

    auto lambdaS = EigenValueUtils::invPowerMethodWithNormInf(matrix).first;
    customPrint(lambdaS);

    for (int k = 1; k < 40; k++) {
        auto mu = lambda1 + k * (lambda501 - lambda1) / 40;
        matrix.addConstOnDiagonal(-mu);
        auto lambda = EigenValueUtils::invPowerMethodWithNormInf(matrix).first + mu;
        customPrint(lambda);
        matrix.addConstOnDiagonal(mu);
    }

    TimerUtil::finish(__func__);

    auto cond2 = abs(lambda1 / lambdaS);
    customPrint(cond2);

    LinearEqLuSolver solver(matrix);
    double det = 1;
    for (int i = 1; i <= matrix.size(); i++)
        det *= solver.getU().at(i, i);
    customPrint(det);
}

int main() {
    cout << setprecision(12);
    for (int i = 1; i <= 1; i++) {
        solve1();
        solve2();
    }
    TimerUtil::printAllTime();
    return 0;
}