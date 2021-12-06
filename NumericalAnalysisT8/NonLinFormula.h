//
// Created by 40461 on 2021/11/26.
//

#ifndef NUMERICALANALYSIST8_NONLINFORMULA_H
#define NUMERICALANALYSIST8_NONLINFORMULA_H

#include <vector>
#include <cassert>

enum BasicType {
    CONSTANT,
    LINEAR,
    SIN,
    COS,
    NONE
};

/**
 * @brief NonLinItem
 * 非线性项，包含一个基本类型和一个系数
 * 支持线性项，常数项，sin，cos
 * 允许括号调用
 */

struct NonLinItem {
    double coef;
    BasicType type;

    double operator()(double v) const;

    NonLinItem derivative() const;
};

/**
 * @brief 非线性表达式
 * 带有非线性项的函数
 */

class NonLinFormula {
public:

    NonLinFormula(std::initializer_list<NonLinItem> list);

    double operator()(std::initializer_list<double> values) const;

    inline NonLinItem &at(int i) {
        assert(i > 0 && i <= data.size());
        return data[i - 1];
    }

    inline const NonLinItem &at(int i) const {
        return const_cast<NonLinFormula *>(this)->at(i);
    }

private:
    std::vector<NonLinItem> data;
};


#endif //NUMERICALANALYSIST8_NONLINFORMULA_H
