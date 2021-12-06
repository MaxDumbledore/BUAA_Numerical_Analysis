//
// Created by 40461 on 2021/11/15.
//

#ifndef NUMERICALANALYSIST2_LINEAREQUTIL_H
#define NUMERICALANALYSIST2_LINEAREQUTIL_H


#include "Matrix.h"

/**
 * @brief ���Է���������
 * ������Ԫ��˹��ȥ������������Է������һ����
 */

class LinearEqUtil {
public:
    /**
     * @brief ���������Է����飨��ռ�ά��Ϊ1��
     * @param matA
     * @param freeVariable ΪΨһ�����ɱ�����ֵ
     * @return Vector һ��������
     */
    static Vector solveHomoLinearEq(const Matrix &matA, double freeVariable);

    static int gaussElimination(Matrix &mat);
};


#endif //NUMERICALANALYSIST2_LINEAREQUTIL_H
