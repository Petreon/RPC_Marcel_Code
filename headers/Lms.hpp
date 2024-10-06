#pragma once
#include "../includes/Eigen/Dense"

/*
Least minimum Square function
*/
typedef struct LmsReturn
{
    Eigen::MatrixXd Xa;
    Eigen::MatrixXd V;
} LmsReturn;

LmsReturn LeastMinSquare(Eigen::MatrixXd A, Eigen::MatrixXd L);