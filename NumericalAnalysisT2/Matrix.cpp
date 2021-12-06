//
// Created by 40461 on 2021/11/9.
//

#include "Matrix.h"
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

Matrix::Matrix(int _n) : n(_n), data(n * n) {}

Matrix Matrix::getDefaultMatrix() {
    Matrix mat(10);
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
            mat.at(i, j) = i == j ? 1.52 * cos(i + 1.2 * j) : sin(0.5 * i + 0.2 * j);
    return mat;
}

Matrix Matrix::transpose() const {
    Matrix mat(n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            mat.at(j, i) = at(i, j);
    return mat;
}

Vector Matrix::operator*(const Vector &v) const {
    assert(n == v.length());
    Vector vec(n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            vec.at(i) += at(i, j) * v.at(j);
    return vec;
}

Matrix Matrix::operator-(const Matrix &m) const {
    assert(n == m.n);
    Matrix mat(n);
    for (int i = 0; i < data.size(); i++)
        mat.data[i] = data[i] - m.data[i];
    return mat;
}

Matrix Matrix::operator*(const Matrix &m) const {
    assert(n == m.n);
    Matrix mat(n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                mat.at(i, j) += at(i, k) * m.at(k, j);
    return mat;
}

Matrix Matrix::operator*(double d) const {
    Matrix mat(n);
    for (int i = 0; i < data.size(); i++)
        mat.data[i] = data[i] * d;
    return mat;
}

Matrix operator*(double d, const Matrix &m) {
    return m * d;
}

void Matrix::print() const {
    cout << fixed << setprecision(3);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cout << at(i, j) << "\t";
        cout << endl;
    }
    cout << endl;
}

Matrix Matrix::getPrefixMat(int m) const {
    assert(m <= n);
    Matrix mat(m);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
            mat.at(i, j) = at(i, j);
    return mat;
}

void Matrix::setPrefixMat(const Matrix &mat) {
    assert(mat.n <= n);
    for (int i = 1; i <= mat.n; i++)
        for (int j = 1; j <= mat.n; j++)
            at(i, j) = mat.at(i, j);
}

Matrix Matrix::operator+(const Matrix &m) const {
    assert(n == m.n);
    Matrix mat(n);
    for (int i = 0; i < data.size(); i++)
        mat.data[i] = data[i] + m.data[i];
    return mat;
}

Matrix Matrix::operator+(double d) const {
    Matrix mat(*this);
    for (int i = 1; i <= n; i++)
        mat.at(i, i) += d;
    return mat;
}

Matrix Matrix::operator-(double d) const {
    return *this + (-d);
}
