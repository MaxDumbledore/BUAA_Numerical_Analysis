//
// Created by 40461 on 2021/10/30.
//

#ifndef NUMERICALANALYSIST1_VECTOR_H
#define NUMERICALANALYSIST1_VECTOR_H

#include <vector>
#include <random>
#include <cassert>

class Vector {
public:
    Vector() = default;

    explicit Vector(int n, bool randomInit = false);

    explicit Vector(std::vector<double> &&_data);

    double norm2() const;

    double normInf() const;

    int maxNormElement() const;

    inline double &at(int i) {
        assert(i >= 1 && i <= data.size());
        return data[i - 1];
    }

    inline const double &at(int i) const {
        return const_cast<Vector *>(this)->at(i);
    }

    inline int length() const {
        return (int) data.size();
    }

    Vector operator/(double t) const;

    double dot(const Vector &v) const;

private:
    std::vector<double> data;
};


#endif //NUMERICALANALYSIST1_VECTOR_H
