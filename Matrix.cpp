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

double Matrix::xhiToX(double xhi, double eta) {
    return xhi;
}

double Matrix::etaToY(double xhi, double eta) const {
    return eta + 4 * a * xhi * xhi - 4 * a * xhi - 8 * a * eta * xhi * xhi + 8 * a * eta * xhi;
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

    double finiteDiffX = finiteDiffUXhi(row, col);
    double finiteDiffY = finiteDiffUEta(row, col);

    double alphaVal = alpha(xhi, eta);
    double betaVal  = beta(xhi, eta);

    return {finiteDiffX + alphaVal * finiteDiffY / betaVal, finiteDiffY / betaVal };
}

double Matrix::finiteDiffUXhi(int row, int col) const {
    double const xhi = col / M;
    double const eta = row / N;

    double dx = 1/M;

    if (xhi == 0) {
        double xhiNext = (col + 1)/M;
        double xhiPrev = col/M;
        return (u(xhiNext,eta) - u(xhiPrev, eta)) / dx;
    } else if (xhi == 1) {
        double xhiNext = col/M;
        double xhiPrev = (col - 1)/M;
        return (u(xhiNext, eta) - u(xhiPrev, eta)) / dx;
    } else {
        double xhiNext = (col + 1)/M;
        double xhiPrev = (col - 1)/M;
        return (u(xhiNext, eta) - u(xhiPrev, eta)) / (2*dx);
    }
}

double Matrix::finiteDiffUEta(int row, int col) const {
    double const xhi = col / M;
    double const eta = row / N;

    double dy = 1/N;

    if (eta == 0) {
        double etaNext = (row + 1)/N;
        double etaPrev =  row/N;
        return (u(xhi,etaNext) - u(xhi, etaPrev)) / dy;
    } else if (eta == 1) {
        double etaNext = row/N;
        double etaPrev = (row - 1)/N;
        return (u(xhi, etaNext) - u(xhi, etaPrev)) / dy;
    } else {
        double etaNext = (row + 1)/N;
        double etaPrev = (row - 1)/N;
        return (u(xhi, etaNext) - u(xhi, etaPrev)) / (2*dy);
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
    std::vector<double> allErrs;

    for (int row = 0; row < N + 1; ++row) {
        for (int col = 0; col < M + 1; ++col) {
            std::array<double,2> exact = duExact(grid[row][col].x, grid[row][col].y);
            std::array<double,2> num   = duNumerical(row, col);

            double ex = abs(exact[0] - num[0]);
            double ey = abs(exact[1] - num[1]);

            accum += ex + ey;
            allErrs.emplace_back(ex + ey);
        }
    }

    double rms = accum / ((M+1)*(N+1));

    double maxErr = *std::max_element(allErrs.begin(), allErrs.end());

    return rms;
}