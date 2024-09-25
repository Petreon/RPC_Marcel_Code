#pragma once
#include "structs.hpp"
#include "../includes/Eigen/Dense"

double ElementNormalization(double value, double OffSetFactor, double ScaleFactor);
Eigen::MatrixXd Normalization(Eigen::MatrixXd img, CorrectionValues correction);