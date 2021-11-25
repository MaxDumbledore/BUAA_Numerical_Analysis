//
// Created by 40461 on 2021/11/9.
//

#include "EigenUtils.h"
#include "ZeroRangeGuard.h"
#include <iostream>
#include <algorithm>

using namespace std;

Matrix EigenUtils::getHessenbergMatrix(const Matrix &mat) {
    auto matA(mat);
    int n = matA.size();
    for (int r = 1; r <= n - 2; r++) {
        /*  bool allZero = true;
            for (int i = r + 2; i <= n && allZero; i++)
                if (!isZero(matA.at(i, r)))
                    allZero = false;
            if (allZero)
                continue;
        */
        double c = 0;
        for (int i = r + 1; i <= n; i++)
            c += matA.at(i, r) * matA.at(i, r);
        c = sqrt(c);
        if (matA.at(r + 1, r) > 0)
            c = -c;
        auto h = c * c - c * matA.at(r + 1, r);
        if (ZeroRangeGuard::isZero(h))
            continue;
        Vector u(n);
        for (int i = r + 1; i <= n; i++)
            u.at(i) = matA.at(i, r);
        u.at(r + 1) -= c;
        auto p = matA.transpose() * u / h;
        auto q = matA * u / h;
        auto t = p.dot(u) / h;
        auto omega = q - t * u;
        matA = matA - omega.outer(u) - u.outer(p);
    }
    return matA;
}

vector<Complex> EigenUtils::solveEigenValuesWithQrMethod(const Matrix &mat, bool printInfo) {
    auto matA = getHessenbergMatrix(mat);
    if (printInfo) {
        cout << "Hessenberg Matrix:" << endl;
        matA.print();
    }
    int n = matA.size(), m = n, k = 1;

    vector<Complex> eigenValues;
    eigenValues.reserve(n);
    while (m > 0) {
        if (m == 1 || ZeroRangeGuard::isZero(matA.at(m, m - 1))) {
            eigenValues.emplace_back(matA.at(m, m));
            --m;
        } else {
            auto t = matA.at(m - 1, m - 1) * matA.at(m, m) - matA.at(m, m - 1) * matA.at(m - 1, m);
            auto s = matA.at(m - 1, m - 1) + matA.at(m, m);
            if ((m == 2 || ZeroRangeGuard::isZero(matA.at(m - 1, m - 2)))) {
                auto delta = sqrt(Complex(s * s - 4 * t));
                eigenValues.emplace_back((s + delta) / 2.0);
                eigenValues.emplace_back((s - delta) / 2.0);
                m -= 2;
            } else {
                auto pMatA = matA.getPrefixMat(m);
                //auto matM = pMatA *pMatA- s * pMatA +t;
                auto matM = (pMatA - s) * pMatA + t;
                updateWithDoubleStep(pMatA, matM);
                matA.setPrefixMat(pMatA);
                ++k;
            }
        }
    }
    if (printInfo)
        cout << "k = " << k << endl;
    reverse(eigenValues.begin(), eigenValues.end());
    if (printInfo) {
        cout << "Matrix after QR Method:" << endl;
        matA.print();
    }
    return eigenValues;
}

void EigenUtils::updateWithDoubleStep(Matrix &matA, const Matrix &matM) {
    auto matB = matM;
    auto &matC = matA;
    int m = matA.size();
    for (int r = 1; r <= m - 1; r++) {
        double c = 0;
        for (int i = r; i <= m; i++)
            c += matB.at(i, r) * matB.at(i, r);
        c = sqrt(c);
        if (matB.at(r, r) > 0)
            c = -c;
        auto h = c * c - c * matB.at(r, r);
        if (ZeroRangeGuard::isZero(h))
            continue;
        Vector u(m);
        for (int i = r; i <= m; i++)
            u.at(i) = matB.at(i, r);
        u.at(r) -= c;

        auto v = matB.transpose() * u / h;
        matB = matB - u.outer(v);
        auto p = matC.transpose() * u / h;
        auto q = matC * u / h;
        auto t = p.dot(u) / h;
        auto omega = q - t * u;
        matC = matC - omega.outer(u) - u.outer(p);
    }
}
