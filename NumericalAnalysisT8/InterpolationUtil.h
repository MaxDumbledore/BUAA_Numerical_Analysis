//
// Created by 40461 on 2021/11/28.
//

#ifndef NUMERICALANALYSIST8_INTERPOLATIONUTIL_H
#define NUMERICALANALYSIST8_INTERPOLATIONUTIL_H

#include <algorithm>
#include "Vector.h"

/**
 * @brief 插值工具类
 * 实现了二维的分片拉格朗日插值法
 */

class InterpolationUtil {
public:
    /**
     * @brief 分片拉格朗日插值法，求出给定点的值
     * @param x 给定点的x坐标
     * @param y 给定点的y坐标
     * @param p 插值点的x坐标列表（length = 3）
     * @param q 插值点的y坐标列表（length = 3）
     * @param m 插值点的原函数值
     * @return 给定点的插值拟合值
     */
    static double twoDimQuadLagrangeInterpolation(double x, double y, const Vector &p, const Vector &q, const Matrix &m);
private:
    /**
     * @brief 求一维拉格朗日插值函数l_k对应的值l_k(x)
     * @param x 给定的坐标
     * @param p 插值点坐标
     * @return 返回{l_k(x) \forall k}组成的向量
     */
    static Vector valueOfLagrangeFunc(double x, const Vector &p);
};


#endif //NUMERICALANALYSIST8_INTERPOLATIONUTIL_H
