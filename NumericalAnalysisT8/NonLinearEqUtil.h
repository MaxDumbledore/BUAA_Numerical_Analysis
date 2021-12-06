//
// Created by 40461 on 2021/11/27.
//

#ifndef NUMERICALANALYSIST8_NONLINEAREQUTIL_H
#define NUMERICALANALYSIST8_NONLINEAREQUTIL_H

#include "NonLinItemMatrix.h"
#include "Vector.h"

class NonLinearEqUtil {
public:
    /**
     * @brief 用牛顿迭代法求解非线性方程组
     * @param mat 非线性矩阵
     * @param c 常量向量
     * @param initX 迭代初始值
     * @return 返回mat*x=c的解
     */
    static Vector solveByNewtonMethod(const NonLinItemMatrix &mat, const Vector &c, const Vector &initX);
};


#endif //NUMERICALANALYSIST8_NONLINEAREQUTIL_H
