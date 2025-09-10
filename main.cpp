#include <iostream>
#include "Matrix.h"
#include "FileHandler.h"

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {

    double M = 10;
    double N = 10;

    Matrix mat(0.5, M, N);

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

    return 0;
}