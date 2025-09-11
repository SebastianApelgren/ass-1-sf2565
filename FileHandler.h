//
// Created by Sebastian Apelgren on 2025-09-10.
//

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "Matrix.h"


class FileHandler {
public:
    static bool writeMatrixToFile(const Matrix& mat, const std::string& filePath);
    static bool writeVectorToFile(const std::vector<double> vec, const std::string& filePath);
};


#endif //FILEHANDLER_H
