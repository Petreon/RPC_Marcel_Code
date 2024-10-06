#include "MatrixSubSetting.hpp"

Eigen::MatrixXd MatrixSubSetting(Eigen::MatrixXd OriginalMatrix, Eigen::MatrixXd IndexMatrix)
{
    int size = IndexMatrix.cols();
    int index = 0;
    Eigen::MatrixXd newPointsMatrix(size,1); // im using columns becaus the index train is comming as a vector of 1xN

    for (int i = 0; i < size; i++) {
        index = (int)IndexMatrix(0, i);
        newPointsMatrix(i, 0) = OriginalMatrix(index, 0);
    }

    return newPointsMatrix;
}