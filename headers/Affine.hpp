#pragma once
#include "../includes/Eigen/Dense"

typedef struct AffineReturn
{
    Eigen::MatrixXd Xa;
    Eigen::MatrixXd V;
} AffineReturn;


AffineReturn Affine(Eigen::MatrixXd Line, Eigen::MatrixXd Sample, Eigen::MatrixXd LineMeas, Eigen::MatrixXd SampleMeas);