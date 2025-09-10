//
// Created by Sebastian Apelgren on 2025-09-08.
//

#include "Matrix.h"
#include "Point.h"
#include <vector>

Matrix::Matrix(const double a, const double M, const double N) {
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

Point Matrix::generatePoint(const int row, const int col) const {
    double const xhi = col / N;
    double const eta = row / M;

    return projSummation(xhi, eta);
}

Point Matrix::rFunction(double xhi, double eta) const {
    if (eta == 0) {
        return {xhi, 4*a*(xhi-1)*xhi};
    } if (eta == 1) {
        return {xhi, 1-4*a*(xhi-1)*xhi};
    } if (xhi == 0 || xhi == 1) {
        return {xhi, eta};
    }
    return {0,0};
}

Point Matrix::projXhi(const double xhi, const double eta) const {
    return rFunction(0,eta) * (1-xhi) + rFunction(1,eta) * xhi;
}

Point Matrix::projEta(const double xhi, const double eta) const {
    return rFunction(xhi,0) * (1-eta) + rFunction(xhi,1) * eta;
}

Point Matrix::projProduct(const double xhi, const double eta) const {
    return rFunction(0,0) * (1 - xhi) * (1 - eta) + rFunction(0,1) * eta * (1 - xhi) +
        rFunction(1,0) * xhi * (1 - eta) + rFunction(1,1) * eta * xhi;
}

Point Matrix::projSummation(const double xhi, const double eta) const {
    return projEta(xhi, eta) + projXhi(xhi, eta) - projProduct(xhi, eta);
}



