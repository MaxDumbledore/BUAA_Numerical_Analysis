//
// Created by 40461 on 2021/11/26.
//

#include "NonLinFormula.h"
#include <cmath>

using namespace std;

NonLinFormula::NonLinFormula(initializer_list<NonLinItem> list) : data(list) {}

double NonLinFormula::operator()(initializer_list<double> values) const {
    assert(values.size() == data.size());
    double res = 0;
    int i = 0;
    for (auto &p: data)
        res += p(values.begin()[i++]);
    return res;
}

double NonLinItem::operator()(double v) const {
    switch (type) {
        case CONSTANT:
            return coef;
        case LINEAR:
            return coef * v;
        case SIN:
            return coef * sin(v);
        case COS:
            return coef * cos(v);
        default:;
    }
    return 0;
}

NonLinItem NonLinItem::derivative() const {
    switch (type) {
        case CONSTANT:
            return {0, CONSTANT};
        case LINEAR:
            return {coef, CONSTANT};
        case SIN:
            return {coef, COS};
        case COS:
            return {-coef, SIN};
        default:;
    }
    return {0, NONE};
}
