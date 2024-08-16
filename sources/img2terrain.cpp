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
 - a1,b1,c1,d1 and a2,b2,c2,d2: which are the numerators and denominators of the PRF - Polinomial Rational Functions
 - Correction values for the three coordinates, and for each one of the images
    - Offset and Scale values

it returns three matrixes, each for a coordinate, and in the position of the pixel related the lat,long,h in that index
 - latitude
 - longitude
 - altitude

does this octave operation:
	function [latitude, longitude, altitude] = img2terrain(Line1, Sample1, Line2, Sample2, a1, b1, c1, d1, a2, b2 ,c2 ,d2, Line_off1, Sample_off1, Lat_off1, Long_off1, H_off1, Line_scale1, Sample_scale1, Lat_scale1, Long_scale1, H_scale1, Line_off2, Sample_off2, Lat_off2, Long_off2, H_off2, Line_scale2, Sample_scale2, Lat_scale2, Long_scale2, H_scale2) 
*/

Coordinates SpacialInterssection(Eigen::MatrixXd aCoefImg1, Eigen::MatrixXd bCoefImg1, Eigen::MatrixXd cCoefImg1, Eigen::MatrixXd dCoefImg1, Eigen::MatrixXd aCoefImg2, 
                                Eigen::MatrixXd bCoefImg2, Eigen::MatrixXd cCoefImg2, Eigen::MatrixXd dCoefImg2, Eigen::MatrixXd Line1, Eigen::MatrixXd Sample1, 
                                Eigen::MatrixXd Line2, Eigen::MatrixXd Sample2, CorrectionValues l1Correction, CorrectionValues s1Correction, CorrectionValues l2Correction, 
                                CorrectionValues s2Correction, CorrectionValues latCorrection1, CorrectionValues longCorrection1, CorrectionValues hCorrection1, 
                                CorrectionValues latCorrection2, CorrectionValues longCorrection2, CorrectionValues hCorrection2){

// Normalization of Line and Sample  Values for both images
    Eigen::MatrixXd l1 = Normalization(Line1, l1Correction);
    Eigen::MatrixXd s1 = Normalization(Line1, s1Correction);
    Eigen::MatrixXd l2 = Normalization(Line1, l2Correction);
    Eigen::MatrixXd s2 = Normalization(Line1, s2Correction);
    

/*
This section uses the first 4 coeficients of the Polinomial Rational Function 
to aproximate initial values for the line and collumn of the pixel in both images.
- l indicates the LINE Polinomial and s the COLLUMN Polinomial.
-   At the end, line and collumn should be:
        l = (a0_Img1 + a1_Img1 + a2_Img1 + a3_Img1) / (b0_Img1 + b1_Img1 + b2_Img1 + b3_Img1)
	s = (c0_Img2 + c1_Img2 + c2_Img2 + c3_Img2) / (d0_Img2 + d1_Img2 + d2_Img2 + d3_Img2)
*/

    double a0_Img1 =   aCoefImg1(0,0) * longCorrection1.scale * latCorrection1.scale * hCorrection1.scale - 
                                aCoefImg1[1] * longCorrection1.off * latCorrection1.scale * hCorrection1.scale - 
                                aCoefImg1[2] * longCorrection1.scale * latCorrection1.off * hCorrection1.scale -
                                aCoefImg1[3] * longCorrection1.scale * latCorrection1.scale * hCorrection1.off;
    
    double a1_Img1 =   aCoefImg1[1] * latCorrection1.scale * hCorrection1.scale;

    double a2_Img1 =   aCoefImg1[2] * longCorrection1.scale * hCorrection1.scale;

    double a3_Img1 =   aCoefImg1[3] * longCorrection1.scale * latCorrection1.scale;


    double b0_Img1 =                * longCorrection1.scale * latCorrection1.scale * hCorrection1.scale - 
                                bCoefImg1[1] * longCorrection1.off * latCorrection1.scale * hCorrection1.scale - 
                                bCoefImg1[2] * longCorrection1.scale * latCorrection1.off * hCorrection1.scale -
                                bCoefImg1[3] * longCorrection1.scale * latCorrection1.scale * hCorrection1.off;
    
    double b1_Img1 =   bCoefImg1[1] * latCorrection1.scale * hCorrection1.scale;

    double b2_Img1 =   bCoefImg1[2] * longCorrection1.scale * hCorrection1.scale;

    double b3_Img1 =   bCoefImg1[3] * longCorrection1.scale * latCorrection1.scale;

	
    double c0_Img1 =   cCoefImg1[0] * longCorrection1.scale * latCorrection1.scale * hCorrection1.scale - 
                                cCoefImg1[1] * longCorrection1.off * latCorrection1.scale * hCorrection1.scale - 
                                cCoefImg1[2] * longCorrection1.scale * latCorrection1.off * hCorrection1.scale -
                                cCoefImg1[3] * longCorrection1.scale * latCorrection1.scale * hCorrection1.off;
    
    double c1_Img1 =   cCoefImg1[1] * latCorrection1.scale * hCorrection1.scale;

    double c2_Img1 =   cCoefImg1[2] * longCorrection1.scale * hCorrection1.scale;

    double c3_Img1 =   cCoefImg1[3] * longCorrection1.scale * latCorrection1.scale;


    double d0_Img1 =                * longCorrection1.scale * latCorrection1.scale * hCorrection1.scale - 
                                dCoefImg1[1] * longCorrection1.off * latCorrection1.scale * hCorrection1.scale - 
                                dCoefImg1[2] * longCorrection1.scale * latCorrection1.off * hCorrection1.scale -
                                dCoefImg1[3] * longCorrection1.scale * latCorrection1.scale * hCorrection1.off;
    
    double d1_Img1 =   dCoefImg1[1] * latCorrection1.scale * hCorrection1.scale;

    double d2_Img1 =   dCoefImg1[2] * longCorrection1.scale * hCorrection1.scale;

    double d3_Img1 =   dCoefImg1[3] * longCorrection1.scale * latCorrection1.scale;


// Since this operation requires 2 images, now we repeat the same operations above for the second image.  

    double a0_Img2 =   aCoefImg2(0,0) * longCorrection1.scale * latCorrection1.scale * hCorrection1.scale - 
                                aCoefImg2[1] * longCorrection1.off * latCorrection1.scale * hCorrection1.scale - 
                                aCoefImg2[2] * longCorrection1.scale * latCorrection1.off * hCorrection1.scale -
                                aCoefImg2[3] * longCorrection1.scale * latCorrection1.scale * hCorrection1.off;
    
    double a1_Img2 =   aCoefImg2[1] * latCorrection1.scale * hCorrection1.scale;

    double a2_Img2 =   aCoefImg2[2] * longCorrection1.scale * hCorrection1.scale;

    double a3_Img2 =   aCoefImg2[3] * longCorrection1.scale * latCorrection1.scale;


    double b0_Img2 =                * longCorrection1.scale * latCorrection1.scale * hCorrection1.scale - 
                                bCoefImg2[1] * longCorrection1.off * latCorrection1.scale * hCorrection1.scale - 
                                bCoefImg2[2] * longCorrection1.scale * latCorrection1.off * hCorrection1.scale -
                                bCoefImg2[3] * longCorrection1.scale * latCorrection1.scale * hCorrection1.off;
    
    double b1_Img2 =   bCoefImg2[1] * latCorrection1.scale * hCorrection1.scale;

    double b2_Img2 =   bCoefImg2[2] * longCorrection1.scale * hCorrection1.scale;

    double b3_Img2 =   bCoefImg2[3] * longCorrection1.scale * latCorrection1.scale;



    double c0_Img2 =   cCoefImg2[0] * longCorrection1.scale * latCorrection1.scale * hCorrection1.scale - 
                                cCoefImg2[1] * longCorrection1.off * latCorrection1.scale * hCorrection1.scale - 
                                cCoefImg2[2] * longCorrection1.scale * latCorrection1.off * hCorrection1.scale -
                                cCoefImg2[3] * longCorrection1.scale * latCorrection1.scale * hCorrection1.off;
    
    double c1_Img2 =   cCoefImg2[1] * latCorrection1.scale * hCorrection1.scale;

    double c2_Img2 =   cCoefImg2[2] * longCorrection1.scale * hCorrection1.scale;

    double c3_Img2 =   cCoefImg2[3] * longCorrection1.scale * latCorrection1.scale;


    double d0_Img2 =                * longCorrection1.scale * latCorrection1.scale * hCorrection1.scale - 
                                dCoefImg2[1] * longCorrection1.off * latCorrection1.scale * hCorrection1.scale - 
                                dCoefImg2[2] * longCorrection1.scale * latCorrection1.off * hCorrection1.scale -
                                dCoefImg2[3] * longCorrection1.scale * latCorrection1.scale * hCorrection1.off;
    
    double d1_Img2 =   dCoefImg2[1] * latCorrection1.scale * hCorrection1.scale;

    double d2_Img2 =   dCoefImg2[2] * longCorrection1.scale * hCorrection1.scale;

    double d3_Img2 =   dCoefImg2[3] * longCorrection1.scale * latCorrection1.scale;

/*
This section does the matrix multiplications as in a iterative method
The purpose is to aproximate initial values through Least Squares, to later ajustment
*/
    Eigen::Matrix<double,4,3> A;
    Eigen::Matrix<double,4,1> L;
    Eigen::MatrixXd Xa;
    for (int i = 0; i < Line1.rows(); i++)
    {
         A << a1_Img1-l1[i]*b1_Img1, a2_Img1-l1[i]*b2_Img1, a3_Img1-l1[i]*b3_Img1,
              c1_Img1-s1[i]*d1_Img1, c2_Img1-s1[i]*d2_Img1, c3_Img1-s1[i]*d3_Img1,
              a1_Img2-l2[i]*b1_Img2, a2_Img2-l2[i]*b2_Img2, a3_Img2-l2[i]*b3_Img2,
              c1_Img2-s2[i]*d1_Img2, c2_Img2-s2[i]*d2_Img2, c3_Img2-s2[i]*d3_Img2;

        L << l1[i]*b0_Img1 - a0_Img1, 
             s1[0]*d0_Img1 - c0_Img1,
             l2[i]*b0_Img2 - a0_Img2, 
             s2[0]*d0_Img2 - c0_Img2;

        Xa = mmq(A,L).Xa;
    }
    
    /*
    This section selects indexes of the elements in the Xa matrix 
    that correspond to LONG, LAT and H
    After that, it alocates those in a correspondent matrix
    */

    Eigen::Matrix<double,Xa.rows(),1> PontosLong;
    Eigen::Matrix<double,Xa.rows(),1> PontosLat;
    Eigen::Matrix<double,Xa.rows(),1> Pontosh;
    
    for (int i = 0; i < Line1.rows(); i++){
        PontosLong(i,1) = 3*i-2;
        PontosLat(i,1) = 3*i-1;
        Pontosh(i,1) = 3*i;
    }

    /*in octave:
    Long = Xa(Pontoslong);
    Lat = Xa(Pontoslat);
    h = Xa(Pontosh);
    */
}
