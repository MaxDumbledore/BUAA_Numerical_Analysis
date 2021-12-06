//
// Created by 40461 on 2021/11/27.
//

#ifndef NUMERICALANALYSIST8_VECTOR_H
#define NUMERICALANALYSIST8_VECTOR_H

#include <vector>
#include <cassert>

class Matrix;

/**
 * @brief 向量类
 * 实现了一些基本运算
 * @todo 更完善的运算符重载，以及右值重载，减少频繁内存申请的开销
 */

class Vector {
public:
    explicit Vector(int n);

    Vector(std::initializer_list<double> list);

    inline double &at(int i) {
        assert(i > 0 && i <= data.size());
        return data[i - 1];
    }

    inline const double &at(int i) const {
        return const_cast<Vector *>(this)->at(i);
    }

    inline int length() const {
        return (int) data.size();
    }

    Vector operator/(double x) const;

    Vector operator-(const Vector &v) const;

    /**
     * @brief 向量点乘
     * @param v
     * @return self^T * v
     */
    double dot(const Vector &v) const;

    /**
     * @brief 向量外积
     * @param v
     * @return self * v^T
     */
    Matrix outer(const Vector &v) const;

    Vector operator*(double x) const;

    friend Vector operator*(double x, const Vector &v);

    void print() const;

    double normInf() const;

    Vector operator -() const;

    Vector &operator+=(const Vector &v);

private:
    std::vector<double> data;
};


#endif //NUMERICALANALYSIST8_VECTOR_H
