#pragma once
#include "../sources/structs.h"

inline long ElementDesnormalization(long normalaizedValue, long OffSetFactor, long ScaleFactor);
Eigen::MatrixXd ImgDesnormalization(Eigen::MatrixXd img, CorrectionValues desnorCorrection[]);
Eigen::MatrixXd Desnor(Eigen::MatrixXd Matrix_Norm, double off, double scale);