//
// Created by 40461 on 2021/10/30.
//

#include "Vector.h"
#include <random>
#include <chrono>

using namespace std;

Vector::Vector(int n, bool randomInit) : data(n) {
    if (randomInit) {
        static default_random_engine engineForVecGen(chrono::system_clock::now().time_since_epoch().count());
        normal_distribution<double> distribution(0, 3.2);
        for (int i = 1; i <= n; i++)
            at(i) = distribution(engineForVecGen);
    }
}

double Vector::norm2() const {
    double res = 0;
    for (const auto &i:data)
        res += i * i;
    return sqrt(res);
}

Vector Vector::operator/(double t) const {
    Vector r(length());
    for (int i = 1; i <= length(); i++)
        r.at(i) = at(i) / t;
    return r;
}

double Vector::dot(const Vector &v) const {
    double ans = 0;
    for (int i = 1; i <= length(); i++)
        ans += at(i) * v.at(i);
    return ans;
}

Vector::Vector(vector<double> &&_data) : data(move(_data)) {}

double Vector::normInf() const {
    double res = 0;
    for (const auto &i:data)
        res = max(res, i);
    return res;
}

int Vector::maxNormElement() const {
    int r = 1;
    for (int i = 2; i <= length(); i++)
        if (abs(at(r)) < abs(at(i)))
            r = i;
    return r;
}
