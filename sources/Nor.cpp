// Include libraries and functions
#include "../includes/Eigen/Dense"
#include <iostream>
#include "Nor.hpp"

/*
function to take the a general value related to each
point (lat, long, height, line, collumn, for example) and normalize them
*/
double ElementNormalization(double value, double OffSetFactor, double ScaleFactor)
{
    return ((value - OffSetFactor) / ScaleFactor);
}

/*
Function to normalize each element of the matrix
The function takes a struct that holds the offset and scale values for a property
*/
Eigen::MatrixXd Normalization(Eigen::MatrixXd img, CorrectionValues correction)
{
    int row = img.rows();
    int col = img.cols();

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            img(i, j) = ElementNormalization(img(i, j), correction.off, correction.scale);
        }
    }
    return img;
}
