//
// Created by 40461 on 2021/11/9.
//

#ifndef NUMERICALANALYSIST2_EIGENUTILS_H
#define NUMERICALANALYSIST2_EIGENUTILS_H

#include "Matrix.h"
#include <complex>

//采用std::complex作为复数的默认实现

using Complex = std::complex<double>;

/**
 * @brief 计算矩阵的特征值
 * 采用了双步位移优化的QR方法
 */

class EigenUtils {
public:
    /**
     *
     * @param mat
     * @param printInfo 如果为true，则打印一些过程信息，包括Hessenberg矩阵，迭代次数等
     * @return std::vector<Complex> 特征值列表
     */
    static std::vector<Complex>
    solveEigenValuesWithQrMethod(const Matrix &mat, bool printInfo = false);

private:

    /**
     * @brief 计算拟上三角(Hessenberg)矩阵
     * @param mat
     * @return Hessenberg矩阵
     */
    static Matrix getHessenbergMatrix(const Matrix &mat);

    /**
     * @brief 通过M矩阵的QR分解来更新矩阵A
     * @param matA，可以修改，A=Q^T*A*Q
     * @param matM
     * @return void
     */
    static void updateWithDoubleStep(Matrix &matA, const Matrix &matM);
};


#endif //NUMERICALANALYSIST2_EIGENUTILS_H
