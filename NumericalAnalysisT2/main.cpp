#include <iostream>
#include <iomanip>
#include <chrono>
#include "Matrix.h"
#include "EigenUtils.h"
#include "LinearEqUtil.h"
#include "ZeroRangeGuard.h"

using namespace std;
using namespace chrono;

/**
 * @brief 自定义的输出浮点数函数
 * @param arg
 * @return std::string
 * 采用e型输出实型数来表示arg，显示12位有效数字，返回表示的字符串
 */

string toScientific(double arg) {
    stringstream ss;
    ss << fixed << setprecision(12);
    auto exp = (arg == 0) ? 0 : 1 + (int) floor(log10(fabs(arg)));
    auto base = (long long) round(arg * pow(10, ss.precision() - exp));
    if (base < 0)
        ss << '-';
    ss << '.' << abs(base) << 'E' << (exp >= 0 ? '+' : '-') << setw(2) << setfill('0') << abs(exp);
    return ss.str();
}

int main() {
    ios::sync_with_stdio(false);
    //如果是调试模式，则输出，否则不输出
#ifdef NDEBUG
    cout.setstate(ios_base::failbit);
#endif
    auto start = system_clock::now();

    auto matA = Matrix::getDefaultMatrix();
    auto n = matA.size();

    //计算矩阵的特征值
    ZeroRangeGuard guard1(1e-13);
    auto eigenValues = EigenUtils::solveEigenValuesWithQrMethod(matA, true);

    //计算矩阵的特征向量
    ZeroRangeGuard guard2(1e-12);
    for (int i = 0; i < n; i++) {
        //如果特征值非实数，则不计算特征向量
        if (eigenValues[i].imag() != 0) {
            cout << "eigenValue: " << "(" << toScientific(eigenValues[i].real()) << ", "
                 << toScientific(eigenValues[i].imag()) << ")" << endl;
            cout << endl;
            continue;
        }
        cout << "eigenValue: " << toScientific(eigenValues[i].real()) << "\t";

        //求解齐次线性方程组
        auto eigenVector = LinearEqUtil::solveHomoLinearEq(matA - eigenValues[i].real(), 1.0);
        eigenVector.normalize();

        cout << "eigenVector: [";
        for (int j = 1; j <= n; j++)
            cout << toScientific(eigenVector.at(j)) << (j == n ? "]" : ", ");
        cout << endl;

        //计算||A*x-lambda*x||，衡量误差
        cout << "||A*x-lambda*x||="
             << toScientific((matA * eigenVector - eigenValues[i].real() * eigenVector).normInf()) << endl;
        cout << endl;
    }

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
#ifdef NDEBUG
    cout.clear();
#endif
    //输出程序运行时间
    cout << "time: " << duration.count() << " microseconds" << endl;
    return 0;
}
