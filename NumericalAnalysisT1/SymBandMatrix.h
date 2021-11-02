//
// Created by 40461 on 2021/10/30.
//

#ifndef NUMERICALANALYSIST1_SYMBANDMATRIX_H
#define NUMERICALANALYSIST1_SYMBANDMATRIX_H

#include <vector>
#include <cassert>
#include "Vector.h"

class SymBandMatrix {
public:
    SymBandMatrix(int _n, int _width);

    inline double &at(int i, int j) {
        if (i > j)
            std::swap(i, j);
        assert(i >= 1 && j <= n && j - i <= w);
        return data[(i - j + w) * n + (j - 1)];
    }

    inline const double &at(int i, int j) const {
        return const_cast<SymBandMatrix *>(this)->at(i, j);
    }

    inline int size() const {
        return n;
    }

    inline int width() const {
        return w;
    }

    Vector operator*(const Vector &v) const;

    void addConstOnDiagonal(double cv);

    static SymBandMatrix genDefaultMatrix();

private:
    int n, w;
    //std::vector<std::vector<double>> data;
    std::vector<double> data;
};

#endif //NUMERICALANALYSIST1_SYMBANDMATRIX_H