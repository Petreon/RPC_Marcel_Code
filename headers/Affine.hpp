#pragma once
#include "structs.hpp"
#include "../includes/Eigen/Dense"


AffineReturn Affine(Eigen::MatrixXd Line, Eigen::MatrixXd Sample, Eigen::MatrixXd LineMeas, Eigen::MatrixXd SampleMeas);