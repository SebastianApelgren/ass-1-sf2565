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
    Matrix(double a, double M, double N);
private:
    Point generatePoint(int row, int col);
    Point rFunction(double xhi, double eta);
    Point projXhi(double xhi, double eta);
    Point projEta(double xhi, double eta);
    Point projPoduct(double xhi, double eta);
    Point projSummation(double xhi, double eta);
};


#endif //UNTITLED_MATRIX_H