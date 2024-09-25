#pragma once
#include "structs.hpp"
#include "../includes/Eigen/Dense"

double Polrfm(double b, double l, double h, Eigen::MatrixXd rpc);
Eigen::MatrixXd Polrfm(Eigen::MatrixXd B, Eigen::MatrixXd L, Eigen::MatrixXd H, Eigen::MatrixXd RPC);