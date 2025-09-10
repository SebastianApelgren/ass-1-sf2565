//
// Created by Sebastian Apelgren on 2025-09-10.
//

#include "FileHandler.h"
#include "Matrix.h"
#include <iostream>
#include <fstream>


bool FileHandler::writeMatrixToFile(const Matrix& mat, const std::string& filePath) {
    std::ofstream file(filePath);

    if (!file) {
        return false;
    }

    double amountRow = mat.N;
    int counter = 0;
    for ( const std::vector<Point>& row : mat.grid ) {
        for (const Point& p : row) {
            file << p;
        }
        ++counter;
        if (counter < amountRow) {
            file << "\n";
        }
    }

    return true;
}