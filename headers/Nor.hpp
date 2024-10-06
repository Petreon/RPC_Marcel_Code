#pragma once
#include "../includes/Eigen/Dense"
#include "img2terrain.hpp" //to include the CorrectionValues


double ElementNormalization(double value, double OffSetFactor, double ScaleFactor);
Eigen::MatrixXd Normalization(Eigen::MatrixXd img, CorrectionValues correction[]);