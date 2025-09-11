//
// Created by Sebastian Apelgren on 2025-09-08.
//

#include "Matrix.h"

#include <iostream>

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
    grid.assign(N+1, std::vector<Point>(M+1));

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

double Matrix::u(const double x, const double y) {
    return sin(x) + cos(y);
}

std::array<double,2> Matrix::duExact(const double x, const double y) {
    return {cos(x), -sin(y)};
}

std::array<double, 2> Matrix::duNumerical(int row,  int col) const {
    double const xhi = col / M;
    double const eta = row / N;

    if (xhi == 0) {
        double uXhiSideDiff = (u((col+1)/M,eta) - u(col/M, eta)) / N;
        double uEtaCentDiff = (u(xhi, (row+1)/N) - u(xhi, (row-1)/N))/(2/N);
        return {uXhiSideDiff + alpha(xhi, eta) / beta(xhi, eta) * uEtaCentDiff , 1 / beta(xhi, eta) * uEtaCentDiff };
    } else if (xhi == 1) {
        double uXhiSideDiff = (u(col/M, eta) - u((col-1)/M, eta)) / M;
        double uEtaCentDiff = (u(xhi, (row+1)/N) - u(xhi, (row-1)/N))/(2/N);
        return {uXhiSideDiff + alpha(xhi, eta) / beta(xhi, eta) * uEtaCentDiff , 1 / beta(xhi, eta) * uEtaCentDiff };
    } else if (eta == 0) {
        double uXhiCentDiff = (u((col+1)/M, eta) - u((col-1)/M, eta))/(2/M);
        double uEtaSideDiff = (u(xhi, (row+1)/N) - u(xhi, row/N)) / N;
        return {uXhiCentDiff + alpha(xhi, eta) / beta(xhi, eta) * uEtaSideDiff , 1 / beta(xhi, eta) * uEtaSideDiff };
    } else if (eta == 1) {
        double uXhiCentDiff = (u((col+1)/M, eta) - u((col-1)/M, eta))/(2/M);
        double uEtaSideDiff = (u(xhi, row/N) - u(xhi, (row-1)/N)) / N;
        return {uXhiCentDiff + alpha(xhi, eta) / beta(xhi, eta) * uEtaSideDiff , 1 / beta(xhi, eta) * uEtaSideDiff };
    } else {
        double uXhiCentDiff = (u((col+1)/M, eta) - u((col-1)/M, eta))/(2/M);
        double uEtaCentDiff = (u(xhi, (row+1)/N) - u(xhi, (row-1)/N))/(2/N);
        return {uXhiCentDiff + alpha(xhi, eta) / beta(xhi, eta) * uEtaCentDiff , 1 / beta(xhi, eta) * uEtaCentDiff };
    }
}

double Matrix::alpha(double xhi, double eta) const {
    return - 8 * a * xhi + 4 * a + 16 * eta * a * xhi - 8 * eta * a;
}

double Matrix::beta(double xhi, double eta) const {
    return 1 + 8 * a * xhi * (1 - xhi);
}

double Matrix::calculateError() const {
    double accum = 0.0;

    for (int row = 0; row < N + 1; ++row) {
        for (int col = 0; col < M + 1; ++col) {
            auto exact = duExact(grid[row][col].x, grid[row][col].y);
            auto num   = duNumerical(row, col);

            double ex = exact[0] - num[0];
            double ey = exact[1] - num[1];

            accum += ex*ex + ey*ey;
        }
    }

    return std::sqrt(accum / ((M+1)*(N+1)));
}