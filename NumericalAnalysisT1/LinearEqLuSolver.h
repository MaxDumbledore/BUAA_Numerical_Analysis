//
// Created by 40461 on 2021/10/30.
//

#ifndef NUMERICALANALYSIST1_LINEAREQLUSOLVER_H
#define NUMERICALANALYSIST1_LINEAREQLUSOLVER_H

#include "Vector.h"
#include "SymBandMatrix.h"

using LeftMatrix = SymBandMatrix;
using UpMatrix = SymBandMatrix;

/**
 * @brief 线性方程组求解类
 */

class LinearEqLuSolver {
public:
    /**
     * @brief 构造函数
     * 通过参数matrix分解出LU矩阵并存储
     * @param matrix
     */
    explicit LinearEqLuSolver(const SymBandMatrix &matrix);

    /**
     * @brief 求解线性方程组
     * 求解方式Ly=b,Ux=y
     * @param 常数向量
     * @return 返回Ax=b的解
     */
    Vector solveEq(const Vector &b);

private:
    LeftMatrix l;
    UpMatrix u;
public:
    /**
     * @brief 得到L
     * @return 下三角矩阵L的常引用
     */
    const LeftMatrix &getL() const;
    /**
     * @brief 得到R
     * @return 上三角矩阵U的常引用
     */
    const UpMatrix &getU() const;

private:
    int n,s;
};


#endif //NUMERICALANALYSIST1_LINEAREQLUSOLVER_H
