//
// Created by 40461 on 2021/10/30.
//

#ifndef NUMERICALANALYSIST1_SYMBANDMATRIX_H
#define NUMERICALANALYSIST1_SYMBANDMATRIX_H

#include <vector>
#include <cassert>
#include "Vector.h"

/**
 * @brief 实对称带状矩阵
 * 内部采用压缩存储方式 A(i,j)
 */

class SymBandMatrix {
public:
    SymBandMatrix(int _n, int _width);

    /**
     * @brief 下标索引方法
     * 我们只存储上三角部分，并将上三角部分进行压缩映射
     * @param i 行参数
     * @param j 列参数
     * @return  返回未压缩矩阵(i,j)位置元素的引用，注意(i,j)和(j,i)返回的是同一个引用
     */
    inline double &at(int i, int j) {
        if (i > j)
            std::swap(i, j);
        assert(i >= 1 && j <= n && j - i <= w);
        return data[(i - j + w) * n + (j - 1)];
    }

    inline const double &at(int i, int j) const {
        return const_cast<SymBandMatrix *>(this)->at(i, j);
    }

    inline int size() const {
        return n;
    }

    inline int width() const {
        return w;
    }

    /**
     * @brief 和向量的乘法
     * @param v
     * @return product A*v
     */
    Vector operator*(const Vector &v) const;

    /**
     * @brief 带原点平移
     * @param cv
     * A=A+cv*I
     */
    void addConstOnDiagonal(double cv);

    /**
     * @brief 生成题目中需要求解的默认矩阵
     * @return 待求解矩阵
     */
    static SymBandMatrix genDefaultMatrix();

private:
    int n, w;
    //std::vector<std::vector<double>> data;
    std::vector<double> data;
};

#endif //NUMERICALANALYSIST1_SYMBANDMATRIX_H