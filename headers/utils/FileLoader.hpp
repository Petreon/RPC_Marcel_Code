#ifndef FILE_LOADER_HPP
#define FILE_LOADER_HPP

#include "../../includes/Eigen/Dense"
#include <string>
#include <vector>

class FileLoader {
public:
    static Eigen::MatrixXd loadMatrixFromFile(const std::string& filePath);
    static Eigen::MatrixXd loadAndConcatenateMatrices(const std::string& filePath1, const std::string& filePath2, const std::vector<int>& pontosOK);
};

#endif // FILE_LOADER_HPP
