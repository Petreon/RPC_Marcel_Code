// Include libraries and functions
#include "../includes/Eigen/Dense"
#include "mmq.cpp"
#include <iostream>
#include "structs.h"

/*
struct to acesses the offset and scale
values for a property to be normalized
*/

// functions

/*
function to take the a general value related to each
point (lat, long, height, line, collumn, for example) and normalize them
*/
long ElementNormalization(long value, long OffSetFactor, long ScaleFactor)
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
