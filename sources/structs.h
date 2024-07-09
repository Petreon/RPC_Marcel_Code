#pragma once
#include "../includes/Eigen/Dense"

typedef struct CorrectionValues
{
    long scale;
    long off;
} CorrectionValues;

typedef struct mmqReturn
{
    Eigen::MatrixXd Xa;
    Eigen::MatrixXd V;
} mmqReturn;

typedef struct AffineReturn
{
    Eigen::MatrixXd Xa;
    Eigen::MatrixXd V;
} AffineReturn;

typedef struct Coordinates
{
    Eigen::MatrixXd Lat;
    Eigen::MatrixXd Long;
    Eigen::MatrixXd altitude;
}