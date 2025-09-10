//
// Created by Sebastian Apelgren on 2025-09-08.
//

#include "Matrix.h"
#include "Point.h"
#include <vector>

Matrix::Matrix(double a, double M, double N) {
    this->a = a;
    this->M = M;
    this->N = N;
    this-> grid = std::vector<std::vector<Point>>(M+1, std::vector<Point>(N+1));

    for ( int row = 0 ; row < M +1 ; ++row) {
        for ( int col = 0 ; col < N +1 ; ++col) {
            grid[row][col] = generatePoint(row,col);
        }
    }
}

Point Matrix::generatePoint(int row, int col) {
    double const xhi = col / N;
    double const eta = row / M;

    return projSummation(xhi, eta);
}

Point Matrix::rFunction(double xhi, double eta) {
    if (eta == 0) {
        return {xhi, 4*a*(xhi-1)*xhi};
    } if (eta == 1) {
        return {xhi, 1-4*a*(xhi-1)*xhi};
    } if (xhi == 0 || xhi == 1) {
        return {xhi, eta};
    }
    return {0,0};
}

Point Matrix::projXhi(double xhi, double eta) {
    return rFunction(0,eta) * (1-xhi) + rFunction(1,eta) * xhi;
}

Point Matrix::projEta(double xhi, double eta) {
    return rFunction(xhi,0) * (1-eta) + rFunction(xhi,1) * eta;
}

Point Matrix::projPoduct(double xhi, double eta) {
    return rFunction(0,0) * (1 - xhi) * (1 - eta) + rFunction(0,1) * eta * (1 - xhi) +
        rFunction(1,0) * xhi * (1 - eta) + rFunction(1,1) * eta * xhi;
}

Point Matrix::projSummation(double xhi, double eta) {
    return projEta(xhi, eta) + projXhi(xhi, eta) - projPoduct(xhi, eta);
}



