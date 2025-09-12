#include <iostream>
#include "Matrix.h"
#include "FileHandler.h"
#include <cmath>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {

    //Task 1: Grid Generation

    double M = 5;
    double N = 5;
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
        std::cout << "Wrote matrix to file successfully" << "\n";
    }

    //Task 2: Numerical Derivatives

    mat.a = 0.1;

    int nrOfIterations = 12;

    std::vector<double> stepsVec;
    std::vector<double> errs;

    std::cout << "\n" << "Starting Part 2" << "\n";

     for (int i = 2; i < nrOfIterations; ++i) {
         M = pow(2,i);
         N = pow(2,i);
         mat.resize(M, N);

         double err = mat.calculateError();

         stepsVec.emplace_back(M);
         errs.emplace_back(err);
    }

    FileHandler::writeVectorToFile(stepsVec,   "stepsVec.txt");
    FileHandler::writeVectorToFile(errs, "errors.txt");

    std::cout << "Wrote stepsVec.txt and errors.txt\n";

    //Task 2: varying a
    nrOfIterations = 21;
    M = 100;
    N = 100;

    std::vector<double> aVec;
    std::vector<double> aErrs;

    std::cout << "\n" << "Starting Part 2.2" << "\n";

    for (int i = 0; i < nrOfIterations; ++i) {
        a = i*0.1;
        mat.a = a;
        mat.resize(M, N);

        double err = mat.calculateError();

        aVec.emplace_back(a);
        aErrs.emplace_back(err);
    }

    FileHandler::writeVectorToFile(aVec,   "aVec.txt");
    FileHandler::writeVectorToFile(aErrs, "aErrors.txt");

    std::cout << "Wrote aVec.txt and aErrors.txt\n";

    return 0;
}