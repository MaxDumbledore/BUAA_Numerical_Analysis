//
// Created by 40461 on 2021/11/15.
//

#ifndef NUMERICALANALYSIST2_LINEAREQUTIL_H
#define NUMERICALANALYSIST2_LINEAREQUTIL_H


#include "Matrix.h"

/**
 * @brief 线性方程组的求解
 * 用列主元高斯消去法，求齐次线性方程组的一个解
 */

class LinearEqUtil {
public:
    /**
     * @brief 求解齐次线性方程组（解空间维度为1）
     * @param matA
     * @param freeVariable 为唯一的自由变量赋值
     * @return Vector 一个解向量
     */
    static Vector solveHomoLinearEq(const Matrix &matA, double freeVariable);

    static int gaussElimination(Matrix &mat);
};


#endif //NUMERICALANALYSIST2_LINEAREQUTIL_H
