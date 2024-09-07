// Include libraries and functions
#include "../includes/Eigen/Dense"
#include <iostream>
#include "structs.h"
// functions

inline long ElementDesnormalization(long normalaizedValue, long OffSetFactor, long ScaleFactor)
{
    return (normalaizedValue * ScaleFactor) + OffSetFactor;
};

Eigen::MatrixXd ImgDesnormalization(Eigen::MatrixXd img, CorrectionValues desnorCorrection[])
{
    int row = img.rows();
    int col = img.cols();

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            img(i, j) = ElementDesnormalization(img(i, j), desnorCorrection[0].off, desnorCorrection[0].scale);
        }
    }
    return img;
}

Eigen::MatrixXd Desnor(Eigen::MatrixXd Matrix_Norm, double off, double scale)
{

    Eigen::MatrixXd result = Matrix_Norm * scale;
    result = result.array() + off;

    return result;
}