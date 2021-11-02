//
// Created by 40461 on 2021/10/30.
//

#ifndef NUMERICALANALYSIST1_LINEAREQLUSOLVER_H
#define NUMERICALANALYSIST1_LINEAREQLUSOLVER_H

#include "Vector.h"
#include "SymBandMatrix.h"

using LeftMatrix = SymBandMatrix;
using UpMatrix = SymBandMatrix;

class LinearEqLuSolver {
public:
    explicit LinearEqLuSolver(const SymBandMatrix &matrix);

    Vector solveEq(const Vector &b);

private:
    LeftMatrix l;
    UpMatrix u;
public:
    const LeftMatrix &getL() const;

    const UpMatrix &getU() const;

private:
    int n,s;
};


#endif //NUMERICALANALYSIST1_LINEAREQLUSOLVER_H
