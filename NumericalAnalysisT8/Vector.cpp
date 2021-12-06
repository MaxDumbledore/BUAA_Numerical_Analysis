//
// Created by 40461 on 2021/11/27.
//

#include "Vector.h"
#include "Matrix.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>
#include <chrono>

using namespace std;

Vector::Vector(int n) : data(n) {}

Vector::Vector(std::initializer_list<double> list) : data(list) {}

Vector Vector::operator/(double x) const {
    return *this * (1 / x);
}

double Vector::dot(const Vector &v) const {
    assert(length() == v.length());
    double sum = 0;
    for (int i = 0; i < data.size(); ++i)
        sum += data[i] * v.data[i];
    return sum;
}

Vector Vector::operator-(const Vector &v) const {
    Vector w(length());
    for (int i = 0; i < data.size(); ++i)
        w.data[i] = data[i] - v.data[i];
    return w;
}

Matrix Vector::outer(const Vector &v) const {
    assert(length() == v.length());
    Matrix m(length());
    for (int i = 1; i <= length(); ++i)
        for (int j = 1; j <= v.length(); ++j)
            m.at(i, j) = at(i) * v.at(j);
    return m;
}

Vector Vector::operator*(double x) const {
    Vector v(length());
    for (int i = 0; i < data.size(); ++i)
        v.data[i] = data[i] * x;
    return v;
}

Vector operator*(double x, const Vector &v) {
    return v * x;
}

void Vector::print() const {
    cout << fixed << setprecision(3);
    for (double i: data)
        cout << i << "\t";
    cout << endl;
}

double Vector::normInf() const {
    double v = 0;
    for (auto i: data)
        v = max(v, abs(i));
    return v;
}

Vector Vector::operator-() const {
    Vector v(length());
    for (int i = 0; i < data.size(); ++i)
        v.data[i] = -data[i];
    return v;
}

Vector &Vector::operator+=(const Vector &v) {
    assert(length() == v.length());
    for (int i = 0; i < data.size(); ++i)
        data[i] += v.data[i];
    return *this;
}

