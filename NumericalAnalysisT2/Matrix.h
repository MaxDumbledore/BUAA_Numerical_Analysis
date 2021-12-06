//
// Created by 40461 on 2021/11/9.
//

#ifndef NUMERICALANALYSIST2_MATRIX_H
#define NUMERICALANALYSIST2_MATRIX_H

#include <vector>
#include <cassert>
#include "Vector.h"

/**
 * @brief 矩阵类
 * 实现了一些基本的矩阵和数字，矩阵和向量以及矩阵之间的运算
 * @todo 更完善的运算符重载，以及右值重载，减少频繁内存申请的开销
 */

class Matrix {
public:
    explicit Matrix(int _n);

    inline double &at(int i, int j) {
        assert(i > 0 && i <= n && j > 0 && j <= n);
        return data[(i - 1) * n + j - 1];
    }

    inline const double &at(int i, int j) const {
        return const_cast<Matrix *>(this)->at(i, j);
    }

    inline int size() const {
        return n;
    }

    static Matrix getDefaultMatrix();

    Matrix transpose() const;

    Vector operator*(const Vector &v) const;

    Matrix operator+(const Matrix &m) const;

    Matrix operator-(const Matrix &m) const;

    Matrix operator*(const Matrix &m) const;

    Matrix operator*(double d) const;

    friend Matrix operator*(double d, const Matrix &m);

    Matrix operator+(double d) const;

    Matrix operator-(double d) const;

    Matrix getPrefixMat(int m) const;

    void setPrefixMat(const Matrix &mat);

    void print() const;

private:
    int n;
    std::vector<double> data;
};


#endif //NUMERICALANALYSIST2_MATRIX_H
