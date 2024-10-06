#pragma once
#include "../includes/Eigen/Dense"

typedef struct Coordinates
{
    Eigen::MatrixXd Lat;
    Eigen::MatrixXd Long;
    Eigen::MatrixXd Height;
} Coordinates;

typedef struct Coeficients
{
    Eigen::MatrixXd a;
    Eigen::MatrixXd b;
    Eigen::MatrixXd c;
    Eigen::MatrixXd d;
} Coeficients;

typedef struct CorrectionValues
{
    double scale;
    double off;
} CorrectionValues;

Coordinates SpacialInterssection(Coeficients Coefs_Img1, Coeficients Coefs_Img2, Eigen::MatrixXd Line1, Eigen::MatrixXd Sample1, Eigen::MatrixXd Line2, Eigen::MatrixXd Sample2, CorrectionValues l1Correction, CorrectionValues s1Correction, CorrectionValues l2Correction, CorrectionValues s2Correction, CorrectionValues latCorrection1, CorrectionValues longCorrection1, CorrectionValues hCorrection1, CorrectionValues latCorrection2, CorrectionValues longCorrection2, CorrectionValues hCorrection2);