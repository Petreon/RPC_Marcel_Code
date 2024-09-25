#pragma once
#include "../includes/Eigen/Dense"
#include <iostream>

typedef struct CorrectionValues
{
    double scale;
    double off;
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
    Eigen::MatrixXd a;
    Eigen::MatrixXd b;
    Eigen::MatrixXd c;
    Eigen::MatrixXd d;
} Coeficients;

typedef struct RecalcReturn
{
    Eigen::MatrixXd Calc_rpc_nl;
    Eigen::MatrixXd Calc_rpc_ns;
} RecalcReturn;