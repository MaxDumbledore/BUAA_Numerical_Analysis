//
// Created by 40461 on 2021/11/27.
//

#include "Matrix.h"
#include <iostream>
#include <iomanip>

using namespace std;

Matrix::Matrix(int _n) : n(_n), data(n * n) {}

Matrix::Matrix(int _n, std::initializer_list <std::initializer_list<double>> list) : n(_n), data(n * n) {
    int i = 0;
    for (auto &row: list) {
        ++i;
        int j = 0;
        for (auto &col: row) {
            ++j;
            at(i, j) = col;
        }
    }
}

Matrix::Matrix(const vector <Vector> &columnVectors) : n((int) columnVectors.size()), data(n * n) {
    for (int j = 1; j <= n; j++) {
        assert(columnVectors[j - 1].length() == n);
        for (int i = 1; i <= n; i++)
            at(i, j) = columnVectors[j - 1].at(i);
    }
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

Matrix Matrix::indexMultiply(const Matrix &m) const {
    assert(n == m.n);
    Matrix mat(n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            mat.at(i, j) = at(i, j) * m.at(i, j);
    return mat;
}

Matrix Matrix::subMatrix(int i, int j, int m) const {
    assert(i > 0 && i + m - 1 <= n && j > 0 && j + m - 1 <= n);
    Matrix mat(m);
    for (int k = 1; k <= m; k++)
        for (int l = 1; l <= m; l++)
            mat.at(k, l) = at(i + k - 1, j + l - 1);
    return mat;
}

double Matrix::sum() const {
    double sum = 0;
    for (double i: data)
        sum += i;
    return sum;
}

std::vector <Vector> Matrix::getColumnVectors() const {
    std::vector <Vector> vec;
    vec.reserve(n);
    for (int j = 1; j <= n; j++) {
        vec.emplace_back(n);
        auto &t = vec.back();
        for (int i = 1; i <= n; i++)
            t.at(i) = at(i, j);
    }
    return vec;
}
