//
// Created by Sebastian Apelgren on 2025-09-08.
//

#ifndef UNTITLED_MATRIX_H
#define UNTITLED_MATRIX_H

#include "Point.h"
#include <vector>

class Matrix {
public:
    double a;
    double M;
    double N;
    std::vector<std::vector<Point>> grid;
    void fillGridPoints();
    Matrix(double a, double M, double N);
    void resize(double M, double N);

    double calculateError() const;
private:
    Point generatePoint(int row, int col) const;
    Point rFunction(double xhi, double eta) const;
    Point projXhi(double xhi, double eta) const;
    Point projEta(double xhi, double eta) const;
    Point projProduct(double xhi, double eta) const;
    Point projSummation(double xhi, double eta) const;

    double alpha(double xhi, double eta) const;
    double beta(double xhi, double eta) const;

    std::array<double,2> duNumerical(int row, int col) const;
    static double u(double x, double y);
    static std::array<double,2> duExact(double x, double y);
};


#endif //UNTITLED_MATRIX_H