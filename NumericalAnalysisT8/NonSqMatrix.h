//
// Created by 40461 on 2021/11/28.
//

#ifndef NUMERICALANALYSIST8_NONSQMATRIX_H
#define NUMERICALANALYSIST8_NONSQMATRIX_H

#include <vector>
#include <cassert>

class Matrix;

/**
 * @brief 非方阵类
 * 实现了非方阵的矩阵乘法，矩阵的转置等运算
 */

class NonSqMatrix {
public:

    explicit NonSqMatrix(int _m, int _n);

    inline double &at(int i, int j) {
        assert(i>0 && i<=m && j>0 && j<=n);
        return data[(i - 1) * n + j - 1];
    }

    inline const double &at(int i, int j) const {
        return const_cast<NonSqMatrix *>(this)->at(i, j);
    }

    NonSqMatrix operator*(const NonSqMatrix &other) const;

    /**
     * @brief 当n=m时，可以将矩阵转换为方阵
     * @return 方阵
     */
    Matrix toMatrix() const &;

    Matrix toMatrix() &&;

    NonSqMatrix transpose() const;

private:
    friend class Matrix;

    int m, n;
    std::vector<double> data;
};


#endif //NUMERICALANALYSIST8_NONSQMATRIX_H
