#pragma once
#include "../../includes/Eigen/Dense"

/*
this function you insert the index points in a vector or Eigen:Matrix that you want to get from the Matrix
And return a new Matrix with these points
*/

Eigen::MatrixXd MatrixSubSetting(Eigen::MatrixXd OriginalMatrix, Eigen::MatrixXd IndexMatrix);