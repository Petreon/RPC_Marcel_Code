#pragma once
#include "structs.h"
#include "../includes/Eigen/Dense"


AffineReturn Affine(Eigen::MatrixXd Line, Eigen::MatrixXd Sample, Eigen::MatrixXd LineMeas, Eigen::MatrixXd SampleMeas);