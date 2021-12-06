//
// Created by 40461 on 2021/11/26.
//

#ifndef NUMERICALANALYSIST8_NONLINITEMMATRIX_H
#define NUMERICALANALYSIST8_NONLINITEMMATRIX_H


#include "NonLinFormula.h"
#include "Vector.h"
#include <vector>

/**
 * @brief 非线性项矩阵
 * 其中每一个元素是一个非线性项
 */

class NonLinItemMatrix {
public:
    explicit NonLinItemMatrix(int n);

    inline NonLinItem &at(int i, int j) {
        assert(i > 0 && i <= n && j > 0 && j <= n);
        return data[(i - 1) * n + j - 1];
    }

    inline const NonLinItem &at(int i, int j) const {
        return const_cast<NonLinItemMatrix *>(this)->at(i, j);
    }

    inline int size() const {
        return n;
    }

    /**
     * @brief 计算非线性项矩阵的值
     * @param v 每一行未知数的值所组成的向量
     * @return 每一行作为一个非线性表达式，求出的值组成的向量
     */
    Vector operator*(const Vector &v) const;

    /**
     * @brief 计算每一项的函数求导组成的新矩阵
     * @return 求导之后的新矩阵
     */
    NonLinItemMatrix derivative() const;

private:
    int n;
    std::vector<NonLinItem> data;
};


#endif //NUMERICALANALYSIST8_NONLINITEMMATRIX_H
