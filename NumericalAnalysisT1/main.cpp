#include <iostream>
#include <iomanip>
#include "SymBandMatrix.h"
#include "EigenValueUtils.h"
#include "LinearEqLuSolver.h"
#include "TimerUtil.h"
#include <functional>

using namespace std;
using EigenValueMethodType = function<pair<double, Vector>(const SymBandMatrix &)>;

/**
 * @brief 自定义的输出浮点数函数
 * @param arg
 * 采用e型输出实型数显示arg，显示12位有效数字
 */

void customPrint(double arg) {
    TimerUtil::finish("solve");
    cout << fixed << setprecision(12);
    auto exp = (arg == 0) ? 0 : 1 + (int) floor(log10(fabs(arg)));
    auto base = (long long) round(arg * pow(10, cout.precision() - exp));
    if (base < 0)
        cout << '-';
    cout << '.' << abs(base) << 'E' << (exp >= 0 ? '+' : '-') << setw(2) << setfill('0') << abs(exp) << endl;
    cout << defaultfloat;
    TimerUtil::start("solve");
}

/**
 * @brief 求解主体
 * @param 函数对象powerMethod
 * @param 函数对象invPowerMethod
 * 传入幂法和反幂法套件，求解，输出答案
 */

void solve(const EigenValueMethodType &powerMethod, const EigenValueMethodType &invPowerMethod) {
    auto matrix = SymBandMatrix::genDefaultMatrix();
    TimerUtil::start("solve");
    auto lambda1 = powerMethod(matrix).first;
    customPrint(lambda1);

    matrix.addConstOnDiagonal(-lambda1);
    auto lambda501 = powerMethod(matrix).first + lambda1;
    customPrint(lambda501);
    matrix.addConstOnDiagonal(lambda1);

    auto lambdaS = invPowerMethod(matrix).first;
    customPrint(lambdaS);

    for (int k = 1; k < 40; k++) {
        auto mu = lambda1 + k * (lambda501 - lambda1) / 40;
        matrix.addConstOnDiagonal(-mu);
        auto lambda = invPowerMethod(matrix).first + mu;
        customPrint(lambda);
        matrix.addConstOnDiagonal(mu);
    }

    auto cond2 = abs(lambda1 / lambdaS);
    customPrint(cond2);

    LinearEqLuSolver solver(matrix);

    double det = 1;
    for (int i = 1; i <= matrix.size(); i++)
        det *= solver.getU().at(i, i);
    customPrint(det);
    TimerUtil::finish("solve");
}

/**
 * @brief 对EigenValueUtils中函数的包装器
 * @tparam Func
 * @param x
 * @return 一个lambda表达式，相当于为函数设置默认eps=1E-12的绑定
 */
template<typename Func>
inline auto wrapEps(Func x) {
    return [=](auto &&param) { return x(forward<decltype(param)>(param), 1E-12); };
}

int main() {
    ios::sync_with_stdio(false);
    //2-范数套件
    solve(wrapEps(EigenValueUtils::powerMethodWithNorm2),
          wrapEps(EigenValueUtils::invPowerMethodWithNorm2));
    TimerUtil::printAllTime();
    TimerUtil::clear();
    //无穷范数套件
    solve(wrapEps(EigenValueUtils::powerMethodWithNormInf),
          wrapEps(EigenValueUtils::invPowerMethodWithNormInf));
    TimerUtil::printAllTime();
    return 0;
}