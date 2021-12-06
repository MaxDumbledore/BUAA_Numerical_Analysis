#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <chrono>
#include "NonLinearEqUtil.h"
#include "InterpolationUtil.h"
#include "NonSqMatrix.h"
#include "Matrix.h"
#include "LinearEqUtil.h"
#include "ZeroRangeGuard.h"

using namespace std;
using namespace chrono;

/**
 * @brief 自定义的输出浮点数函数
 * @param arg 待输出的浮点数
 * @param precision 精度
 * @return std::string
 * 采用e型输出实型数来表示arg，显示precision（>0）位有效数字，返回表示的字符串
 */

string toScientific(double arg, int precision) {
    stringstream ss;
    ss << fixed << setprecision(precision);
    auto exp = (arg == 0) ? 0 : 1 + (int) floor(log10(fabs(arg)));
    auto base = (long long) round(arg * pow(10, precision - exp));
    if (base == 0) {
        ss << '.';
        ss << setfill('0') << setw(precision) << 0;
    } else {
        if (base < 0)
            ss << '-';
        ss << '.' << abs(base);
    }
    ss << 'E' << (exp >= 0 ? '+' : '-') << setw(2) << setfill('0') << abs(exp);
    return ss.str();
}

int main() {
    ios::sync_with_stdio(false);
    //如果是调试模式，则输出，否则不输出
#ifdef NDEBUG
    cout.setstate(ios_base::failbit);
#endif
    auto start = system_clock::now();

    //关于x,y,t,u,v,w的非线性方程组
    vector<NonLinFormula> funcs = {
            {},
            {{0.5, COS},    {1,   LINEAR}, {1, LINEAR}, {1, LINEAR}, {-1, LINEAR},   {0,  CONSTANT}, {-2.67, CONSTANT}},
            {{1,   LINEAR}, {0.5, SIN},    {1, LINEAR}, {1, LINEAR}, {0,  CONSTANT}, {-1, LINEAR},   {-1.07, CONSTANT}},
            {{0.5, LINEAR}, {1,   LINEAR}, {1, COS},    {1, LINEAR}, {-1, LINEAR},   {0,  CONSTANT}, {-3.74, CONSTANT}},
            {{1,   LINEAR}, {0.5, LINEAR}, {1, LINEAR}, {1, SIN},    {0,  CONSTANT}, {-1, LINEAR},   {-0.79, CONSTANT}}
    };

    //t,u确定z，所产生的二维数表
    Matrix zTable(6, {
            {-0.5,  -0.34, 0.14,  0.94,  2.06,  3.5},
            {-0.42, -0.5,  -0.26, 0.3,   1.18,  2.38},
            {-0.18, -0.5,  -0.5,  -0.18, 0.46,  1.42},
            {0.22,  -0.34, -0.58, -0.5,  -0.1,  0.62},
            {0.78,  -0.02, -0.5,  -0.66, -0.5,  -0.02},
            {1.5,   0.46,  -0.26, -0.66, -0.74, -0.5}
    });

    NonLinItemMatrix matA(4);
    vector<NonLinFormula> fc{{}};
    fc.reserve(5);
    //计算关于t,u,v,w的非线性方程，包括系数非线性矩阵和常数项表达式
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++)
            matA.at(i, j) = funcs[i].at(j);
        fc.emplace_back(initializer_list<NonLinItem>{funcs[i].at(5), funcs[i].at(6), funcs[i].at(7)});
    }
    int m = 10, n = 20;
    NonSqMatrix matU(m + 1, n + 1);

    /**
     * @brief 计算二元函数z=f(x,y)，其中f(x,y)由 ①方程组 ②对zTable插值得到的关于t,u的二元函数 共同确定
     * @param x 参数x
     * @param y 参数y
     * @param z f(x,y)
     */
    auto f = [&](double x, double y) -> auto {
        static Vector b(4), initialVec({1, 1, 1, 1});
        for (int k = 1; k <= 4; k++)
            b.at(k) = fc[k]({x, y, 0});
        //使用牛顿迭代法来求出四元非线性方程组的解，从x,y得到确定的t,u
        auto res = NonLinearEqUtil::solveByNewtonMethod(matA, -b, initialVec);

        auto t = res.at(1), u = res.at(2);
        auto pT = t > 0.8 ? 0.8 : (t < 0.2 ? 0.2 : round(t / 0.2) * 0.2);
        auto pU = u > 1.6 ? 1.6 : (u < 0.4 ? 0.4 : round(u / 0.4) * 0.4);
        auto iT = (int) round(pT / 0.2) + 1;
        auto iU = (int) round(pU / 0.4) + 1;
        //代入关于t,u的插值函数，得到f(x,y)
        return InterpolationUtil::twoDimQuadLagrangeInterpolation(t, u, {pT - 0.2, pT, pT + 0.2},
                                                                  {pU - 0.4, pU, pU + 0.4},
                                                                  zTable.subMatrix(iT - 1, iU - 1, 3));
    };

    //求出数表(x_i,y_j,f(x_i,y_j)),并输出
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= n; j++) {
            auto x = 0.08 * i, y = 0.5 + 0.05 * j;
            matU.at(i + 1, j + 1) = f(x, y);
            cout << toScientific(x, 2) << "\t" << toScientific(y, 3) << "\t"
                 << toScientific(matU.at(i + 1, j + 1), 12) << endl;
        }

    int k = 0;
    double delta;
    ZeroRangeGuard guard(1E-7);
    Matrix matC(0);
    /**
     * @brief 通过固定的系数矩阵C来求出函数值 z' = p(x,y) = \sum_{r=0}^k \sum_{s=0}^k c_{rs} x^r y^s
     * @param x 参数x
     * @param y 参数y
     * @return z' p(x,y)
     */
    auto p = [&](double x, double y) -> auto {
        double xi = 1, res = 0;
        for (int i = 1; i <= matC.size(); i++) {
            double yj = 1;
            for (int j = 1; j <= matC.size(); j++) {
                res += matC.at(i, j) * xi * yj;
                yj *= y;
            }
            xi *= x;
        }
        return res;
    };

    //求最小的k值使得delta满足精度
    do {
        ZeroRangeGuard guard1(1E-12);
        ++k;
        NonSqMatrix matB(m + 1, k + 1), matG(n + 1, k + 1);
        for (int i = 0; i <= m; i++) {
            auto t = 0.08 * i;
            matB.at(i + 1, 1) = 1;
            for (int j = 2; j <= k + 1; j++)
                matB.at(i + 1, j) = matB.at(i + 1, j - 1) * t;
        }
        for (int j = 0; j <= n; j++) {
            auto u = 0.5 + 0.05 * j;
            matG.at(j + 1, 1) = 1;
            for (int i = 2; i <= k + 1; i++)
                matG.at(j + 1, i) = matG.at(j + 1, i - 1) * u;
        }

        //求解方程 (B^T B)C(G^T G) = B^T U G 即可得到系数矩阵C
        Matrix temp = LinearEqUtil::solveByGauss((matB.transpose() * matB).toMatrix(),
                                                 (matB.transpose() * matU * matG).toMatrix().getColumnVectors());
        matC = Matrix(LinearEqUtil::solveByGauss((matG.transpose() * matG).transpose().toMatrix(),
                                                 temp.transpose().getColumnVectors())).transpose();

        delta = 0;
        //计算误差值delta
        for (int i = 0; i <= m; i++)
            for (int j = 0; j <= n; j++) {
                double d = p(0.08 * i, 0.5 + 0.05 * j) - matU.at(i + 1, j + 1);
                delta += d * d;
            }
        cout << "k = " << k << " delta = " << toScientific(delta, 12) << endl;
    } while (!ZeroRangeGuard::isZero(delta));
    cout << "Final acceptable k = " << k << " delta (<=1E-7): " << toScientific(delta, 12) << endl;
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= k; j++)
            cout << toScientific(matC.at(i, j), 12) << "\t";
        cout << endl;
    }

    //打印数表 (x_i^*, y_i^*, f(x_i^*, y_i^*), p(x_i^*, y_i^*))
    for (int i = 1; i <= 8; i++)
        for (int j = 1; j <= 5; j++) {
            double x = 0.1 * i, y = 0.5 + 0.2 * j;
            cout << toScientific(x, 2) << "\t" << toScientific(y, 3) << "\t" << toScientific(f(x, y), 12) << "\t"
                 << toScientific(p(x, y), 12) << endl;
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
