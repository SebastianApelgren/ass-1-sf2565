//
// Created by Sebastian Apelgren on 2025-09-08.
//

#ifndef UNTITLED_MATRIX_H
#define UNTITLED_MATRIX_H

#include "Point.h"
#include <vector>

class Matrix {
public:
    int M = 10;
    int N = 10;
    explicit Matrix(double a);
    std::vector<std::vector<Point>> grid = std::vector<std::vector<Point>>(M, std::vector<Point>(N));

private:
    Point generatePoint(int row, int col, double a);
};


#endif //UNTITLED_MATRIX_H