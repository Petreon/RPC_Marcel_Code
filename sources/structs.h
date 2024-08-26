#pragma once
#include "../includes/Eigen/Dense"
#include <iostream>

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
    Eigen::MatrixXd Height;
} Coordinates;

typedef struct CoordinatesUTM
{
    Eigen::MatrixXd East;
    Eigen::MatrixXd North;
    Eigen::MatrixXd Fuse;
} CoordinatesUTM;

typedef struct Coeficients
{
    Eigen::Matrix<double,20,1> a;
    Eigen::Matrix<double,20,1> b;
    Eigen::Matrix<double,20,1> c;
    Eigen::Matrix<double,20,1> d;
} Coeficients;