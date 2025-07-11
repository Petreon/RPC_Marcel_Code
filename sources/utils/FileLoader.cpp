#include "../headers/utils/FileLoader.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

Eigen::MatrixXd FileLoader::loadMatrixFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    std::vector<double> values;
    double value;
    while (file >> value) {
        values.push_back(value);
    }
    file.close();

    if (values.empty()) {
        return Eigen::MatrixXd(); // Return empty matrix if file is empty
    }

    // Assuming a column vector for now, adjust if needed for general matrices
    Eigen::MatrixXd matrix(values.size(), 1);
    for (size_t i = 0; i < values.size(); ++i) {
        matrix(i, 0) = values[i];
    }
    return matrix;
}

Eigen::MatrixXd FileLoader::loadAndConcatenateMatrices(const std::string& filePath1, const std::string& filePath2, const std::vector<int>& pontosOK) {
    Eigen::MatrixXd matrix1 = loadMatrixFromFile(filePath1);
    Eigen::MatrixXd matrix2 = loadMatrixFromFile(filePath2);

    Eigen::MatrixXd concatenatedMatrix(matrix1.rows() + matrix2.rows(), 1);
    concatenatedMatrix << matrix1, matrix2;

    // Apply pontosOK filter
    Eigen::MatrixXd filteredMatrix(pontosOK.size(), 1);
    for (size_t i = 0; i < pontosOK.size(); ++i) {
        filteredMatrix(i, 0) = concatenatedMatrix(pontosOK[i] - 1, 0); // Adjust for 0-based indexing
    }
    return filteredMatrix;
}
