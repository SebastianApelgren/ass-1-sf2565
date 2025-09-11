#include <iostream>
#include "Matrix.h"
#include "FileHandler.h"
#include <cmath>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {

    //Task 1: Grid Generation

    double M = 10;
    double N = 10;
    double a = 0.5;

    Matrix mat(a, M, N);

    for ( const std::vector<Point>& row : mat.grid ) {
        for (const Point& p : row) {
            std::cout << p;
        }
        std::cout << "\n";
    }

    std::string filePath = "transformed-matrix.txt";
    bool result = FileHandler::writeMatrixToFile(mat, filePath);
    if (!result) {
        std::cout << "Error loading the file";
    } else {
        std::cout << "Wrote matrix to file successfully";
    }

    //Task 2: Numerical Derivatives

    a = 0.1;

    int nrOfIterations = 10;

    for (int i = 2; i < nrOfIterations; i++) {

        M = pow(2,i);
        N = pow(2,i);

        mat.resize(M,N);

    }

    return 0;
}