#pragma once
#include "structs.hpp"
#include "../includes/Eigen/Dense"

Coordinates SpacialInterssection(Coeficients Coefs_Img1, Coeficients Coefs_Img2, Eigen::MatrixXd Line1, Eigen::MatrixXd Sample1, Eigen::MatrixXd Line2, Eigen::MatrixXd Sample2, CorrectionValues l1Correction, CorrectionValues s1Correction, CorrectionValues l2Correction, CorrectionValues s2Correction, CorrectionValues latCorrection1, CorrectionValues longCorrection1, CorrectionValues hCorrection1, CorrectionValues latCorrection2, CorrectionValues longCorrection2, CorrectionValues hCorrection2);