#include "../includes/Eigen/Dense"
#include "mmq.cpp"
#include <iostream>
#include "structs.h"
#include "Nor.cpp"
/* 
This function does the spacial intersection operation, mapping image pixels to ground coordinates,
that is, [latitude,longitude,height]

it takes as its parameters:
 - Line1, Line 2: 
 - Sample1, Sample 2:
 - a1,b1,c1,d1 and a2,b2,c2,d2: 
 - Correction values for the three coordinates, and for each one of the images
    - Offset and Scale values

it returns three matrixes, each for a coordinate, and in the position of the pixel related the lat,long,h in that index
 - latitude
 - longitude
 - altitude


function [latitude, longitude, altitude] = img2terrain(Line1, Sample1, Line2, Sample2, a1, b1, c1, d1, a2, b2 ,c2 ,d2, Line_off1, Sample_off1, Lat_off1, Long_off1, H_off1, Line_scale1, Sample_scale1, Lat_scale1, Long_scale1, H_scale1, Line_off2, Sample_off2, Lat_off2, Long_off2, H_off2, Line_scale2, Sample_scale2, Lat_scale2, Long_scale2, H_scale2) 

*/

Coordinates SpacialInterssection(Eigen::MatrixXd aCoefImg1, Eigen::MatrixXd bCoefImg1, Eigen::MatrixXd cCoefImg1, Eigen::MatrixXd dCoefImg1, Eigen::MatrixXd aCoefImg2, Eigen::MatrixXd bCoefImg2, Eigen::MatrixXd cCoefImg2, Eigen::MatrixXd dCoefImg2 Eigen::MatrixXd Line1, Eigen::MatrixXd Sample1, Eigen::MatrixXd Line2, Eigen::MatrixXd Sample2, CorrectionValues l1Correction, CorrectionValues s1Correction, CorrectionValues l2Correction, CorrectionValues s2Correction, CorrectionValues latCorrection, CorrectionValues longCorrection, CorrectionValues hCorrection){

// Normalization of Line and Sample  Values for both images
    Eigen::MatrixXd l1 = Normalization(Line1, l1Correction);
    Eigen::MatrixXd s1 = Normalization(Line1, s1Correction);
    Eigen::MatrixXd l2 = Normalization(Line1, l2Correction);
    Eigen::MatrixXd s2 = Normalization(Line1, s2Correction);
    
}