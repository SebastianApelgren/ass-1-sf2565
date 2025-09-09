//
// Created by Sebastian Apelgren on 2025-09-08.
//

#include "Matrix.h"
#include "Point.h"
#include <vector>

Matrix::Matrix(double a) {
    for ( int row = 0 ; row < M +1 ; ++row) {
        for ( int col = 0 ; col < N +1 ; ++col) {
            grid[row][col] = generatePoint(row,col,a);
        }
    }
}

Point Matrix::generatePoint(int row, int col, double a) {
    double const xhi = col / N;
    double const neta = row / M;
    if (row == 0) {
        return {xhi, 4*a*(xhi-1)*xhi};
    } if (row == M) {
        return {xhi, 1-4*a*(xhi-1)*xhi};
    } if (col == 0 || col == N) {
        return {xhi, neta};
    }
    return {0,0};
}