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
private:
    Point generatePoint(int row, int col) const;
    Point rFunction(double xhi, double eta) const;
    Point projXhi(double xhi, double eta) const;
    Point projEta(double xhi, double eta) const;
    Point projProduct(double xhi, double eta) const;
    Point projSummation(double xhi, double eta) const;

    static double uFunction(double x, double y);
    static std::array<double,2> duExact(double x, double y);
    static std::array<double,2> duNumerical(double x, double y);

    std::array<double,2> calculateError() const;
};


#endif //UNTITLED_MATRIX_H