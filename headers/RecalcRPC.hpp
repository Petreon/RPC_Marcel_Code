#pragma once
#include "../includes/Eigen/Dense"

typedef struct RecalcReturn
{
    Eigen::MatrixXd Calc_rpc_nl;
    Eigen::MatrixXd Calc_rpc_ns;
} RecalcReturn;

RecalcReturn RecalcRPC(Eigen::MatrixXd Bn, Eigen::MatrixXd Ln, Eigen::MatrixXd Hn, Eigen::MatrixXd rpc_nl, Eigen::MatrixXd rpc_dl, Eigen::MatrixXd rpc_ns, Eigen::MatrixXd rpc_ds, Eigen::MatrixXd LineMeas, Eigen::MatrixXd SampleMeas, double Line_Off, double Line_Scale, double Sample_Off, double Sample_Scale);