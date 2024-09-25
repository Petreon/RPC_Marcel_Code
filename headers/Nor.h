#pragma once

#include "structs.h"
double ElementNormalization(double value, double OffSetFactor, double ScaleFactor);
Eigen::MatrixXd Normalization(Eigen::MatrixXd img, CorrectionValues correction);