//
// Created by 40461 on 2021/11/27.
//

#ifndef NUMERICALANALYSIST8_LINEAREQUTIL_H
#define NUMERICALANALYSIST8_LINEAREQUTIL_H

#include "Vector.h"
#include <vector>

/**
 * @brief 求解线性方程组的解
 * 实现了列主元高斯消去法
 */

class LinearEqUtil {
public:
    /**
     * @brief 列主元高斯消去法，求出每一个A*x=b_i的解向量x_i，其中A为n*n的矩阵，b为n的向量组成的集合
     * @param matA n*n的矩阵
     * @param b 长度为n的向量组成的集合
     * @return {x_i} \forall b_i
     */
    static std::vector<Vector> solveByGauss(Matrix &matA, std::vector<Vector> &b);

    //右值重载
    static std::vector<Vector> solveByGauss(Matrix &&matA, std::vector<Vector> &&b) {
        return solveByGauss(matA, b);
    }
};

#endif //NUMERICALANALYSIST8_LINEAREQUTIL_H
