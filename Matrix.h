//
// Created by Sebastian Apelgren on 2025-09-08.
//

#ifndef UNTITLED_MATRIX_H
#define UNTITLED_MATRIX_H

#include "Point.h"
#include <vector>

class Matrix {
public:
    double M = 10;
    double N = 10;
    explicit Matrix(double a);
    std::vector<std::vector<Point>> grid = std::vector<std::vector<Point>>(M+1, std::vector<Point>(N+1));

private:
    Point generatePoint(int row, int col, double a);
};


#endif //UNTITLED_MATRIX_H