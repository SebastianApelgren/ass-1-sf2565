//
// Created by Sebastian Apelgren on 2025-09-08.
//

#include "Matrix.h"
#include "Point.h"
#include <vector>

void Matrix::fillGridPoints() {
    for ( int row = 0 ; row < N + 1 ; ++row) {
        for ( int col = 0 ; col < M + 1 ; ++col) {
            grid[row][col] = generatePoint(row,col);
        }
    }
}

Matrix::Matrix(const double a, const double M, const double N) {
    this->a = a;
    this->M = M;
    this->N = N;
    this-> grid = std::vector<std::vector<Point>>(N+1, std::vector<Point>(M+1));

    fillGridPoints();
}

void Matrix::resize(double M, double N) {
    this->M = M;
    this->N = N;
    grid.assign(M+1, std::vector<Point>(N+1));

    fillGridPoints();
}

Point Matrix::generatePoint(const int row, const int col) const {
    double const xhi = col / M;
    double const eta = row / N;

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

double Matrix::uFunction(const double x, const double y) {
    return sin(x) + cos(y);
}

std::array<double,2> Matrix::duExact(const double x, const double y) {
    return {cos(x), -sin(y)};
}

std::array<double, 2> Matrix::duNumerical(double x, double y) {
    return {0, 0}; //change
}

std::array<double,2> Matrix::calculateError() const {
    std::array<double, 2> errors = {0,0};
    std::array<double, 2> pDuExact;
    std::array<double, 2> pDuNumerical;

    //L2-Norm
    for ( int row = 0 ; row < N + 1 ; ++row) {
        for ( int col = 0 ; col < M + 1 ; ++col) {
            pDuExact = duExact(grid[row][col].x, grid[row][col].y);
            pDuNumerical = duExact(0, 0); // change

            errors[0] += pow(abs(pDuExact[0] - pDuNumerical[1]), 2);
            errors[1] += pow(abs(pDuExact[0] - pDuNumerical[1]),2);
        }
    }

    errors[0] /= M;
    errors[1] /= N;

    return errors;
}
