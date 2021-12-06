//
// Created by 40461 on 2021/11/27.
//

#include "LinearEqUtil.h"
#include "Matrix.h"
#include <algorithm>

using namespace std;

vector <Vector> LinearEqUtil::solveByGauss(Matrix &matA, vector <Vector> &b) {
    int n = matA.size();
    for (int k = 1; k < n; k++) {
        int i = k;
        //选择第k列中第k行以下元素最大的行
        for (int j = k + 1; j < n; j++)
            if (abs(matA.at(j, k)) > abs(matA.at(i, k)))
                i = j;
        //交换第k行和第i行
        if (i != k) {
            for (int j = k; j <= n; j++)
                swap(matA.at(k, j), matA.at(i, j));
            for (auto &bt: b)
                swap(bt.at(k), bt.at(i));
        }
        //消元
        for (i = k + 1; i <= n; i++) {
            double m = matA.at(i, k) / matA.at(k, k);
            for (int j = k; j <= n; j++)
                matA.at(i, j) -= m * matA.at(k, j);
            for (auto &bt: b)
                bt.at(i) -= m * bt.at(k);
        }
    }
    vector <Vector> res;
    res.reserve(b.size());
    //求解
    for (auto & bt : b) {
        res.emplace_back(bt.length());
        auto &x = res.back();
        for (int k = n; k > 0; k--) {
            double s = 0;
            for (int j = k + 1; j <= n; j++)
                s += matA.at(k, j) * x.at(j);
            x.at(k) = (bt.at(k) - s) / matA.at(k, k);
        }
    }
    return res;
}
