#include "../includes/Eigen/Dense"
#include "mmq.hpp"
#include <iostream>
#include "structs.hpp"
#include "Nor.hpp"
#include "Polrfm.hpp"
#include "Deriv_H.hpp"
#include "Deriv_B.hpp"
#include "Deriv_L.hpp"
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

Coordinates SpacialInterssection(Coeficients Coefs_Img1, Coeficients Coefs_Img2, Eigen::MatrixXd Line1, Eigen::MatrixXd Sample1, Eigen::MatrixXd Line2, Eigen::MatrixXd Sample2, CorrectionValues l1Correction, CorrectionValues s1Correction, CorrectionValues l2Correction, CorrectionValues s2Correction, CorrectionValues latCorrection1, CorrectionValues longCorrection1, CorrectionValues hCorrection1, CorrectionValues latCorrection2, CorrectionValues longCorrection2, CorrectionValues hCorrection2){

// Normalization of Line and Sample  Values for both images
    Eigen::MatrixXd l1 = Normalization(Line1, l1Correction);
    Eigen::MatrixXd s1 = Normalization(Sample1, s1Correction);
    Eigen::MatrixXd l2 = Normalization(Line2, l2Correction);
    Eigen::MatrixXd s2 = Normalization(Sample2, s2Correction);
    

/*
This section uses the first 4 coeficients of the Polinomial Rational Function 
to aproximate initial values for the line and collumn of the pixel in both images.
- l indicates the LINE Polinomial and s the COLLUMN Polinomial.
-   At the end, line and collumn should be:
        l = (a0_Img1 + a1_Img1 + a2_Img1 + a3_Img1) / (b0_Img1 + b1_Img1 + b2_Img1 + b3_Img1)
    s = (c0_Img2 + c1_Img2 + c2_Img2 + c3_Img2) / (d0_Img2 + d1_Img2 + d2_Img2 + d3_Img2)
*/

    double a0_Img1 =   Coefs_Img1.a(0,0) * longCorrection1.scale * latCorrection1.scale * hCorrection1.scale - 
                                Coefs_Img1.a(1,0) * longCorrection1.off * latCorrection1.scale * hCorrection1.scale - 
                                Coefs_Img1.a(2,0) * longCorrection1.scale * latCorrection1.off * hCorrection1.scale -
                                Coefs_Img1.a(3,0) * longCorrection1.scale * latCorrection1.scale * hCorrection1.off;
    
    double a1_Img1 =   Coefs_Img1.a(1,0) * latCorrection1.scale * hCorrection1.scale;

    double a2_Img1 =   Coefs_Img1.a(2,0) * longCorrection1.scale * hCorrection1.scale;

    double a3_Img1 =   Coefs_Img1.a(3,0) * longCorrection1.scale * latCorrection1.scale;


    double b0_Img1 =    longCorrection1.scale * latCorrection1.scale * hCorrection1.scale - 
                        Coefs_Img1.b(1,0) * longCorrection1.off * latCorrection1.scale * hCorrection1.scale - 
                        Coefs_Img1.b(2,0) * longCorrection1.scale * latCorrection1.off * hCorrection1.scale -
                        Coefs_Img1.b(3,0) * longCorrection1.scale * latCorrection1.scale * hCorrection1.off;

    double b1_Img1 =   Coefs_Img1.b(1,0) * latCorrection1.scale * hCorrection1.scale;

    double b2_Img1 =   Coefs_Img1.b(2,0) * longCorrection1.scale * hCorrection1.scale;

    double b3_Img1 =   Coefs_Img1.b(3,0) * longCorrection1.scale * latCorrection1.scale;

    
    double c0_Img1 =   Coefs_Img1.c(0,0) * longCorrection1.scale * latCorrection1.scale * hCorrection1.scale - 
                                Coefs_Img1.c(1,0) * longCorrection1.off * latCorrection1.scale * hCorrection1.scale - 
                                Coefs_Img1.c(2,0) * longCorrection1.scale * latCorrection1.off * hCorrection1.scale -
                                Coefs_Img1.c(3,0) * longCorrection1.scale * latCorrection1.scale * hCorrection1.off;
    
    double c1_Img1 =   Coefs_Img1.c(1,0) * latCorrection1.scale * hCorrection1.scale;

    double c2_Img1 =   Coefs_Img1.c(2,0) * longCorrection1.scale * hCorrection1.scale;

    double c3_Img1 =   Coefs_Img1.c(3,0) * longCorrection1.scale * latCorrection1.scale;


    double d0_Img1 =    longCorrection1.scale * latCorrection1.scale * hCorrection1.scale - 
                        Coefs_Img1.d(1,0) * longCorrection1.off * latCorrection1.scale * hCorrection1.scale - 
                        Coefs_Img1.d(2,0) * longCorrection1.scale * latCorrection1.off * hCorrection1.scale -
                        Coefs_Img1.d(3,0) * longCorrection1.scale * latCorrection1.scale * hCorrection1.off;
    
    double d1_Img1 =   Coefs_Img1.d(1,0) * latCorrection1.scale * hCorrection1.scale;

    double d2_Img1 =   Coefs_Img1.d(2,0) * longCorrection1.scale * hCorrection1.scale;

    double d3_Img1 =   Coefs_Img1.d(3,0) * longCorrection1.scale * latCorrection1.scale;


// Since this operation requires 2 images, now we repeat the same operations above for the second image.  

    double a0_Img2 =   Coefs_Img2.a(0,0) * longCorrection2.scale * latCorrection2.scale * hCorrection2.scale - 
                                Coefs_Img2.a(1,0) * longCorrection2.off * latCorrection2.scale * hCorrection2.scale - 
                                Coefs_Img2.a(2,0) * longCorrection2.scale * latCorrection2.off * hCorrection2.scale -
                                Coefs_Img2.a(3,0) * longCorrection2.scale * latCorrection2.scale * hCorrection2.off;
    
    double a1_Img2 =   Coefs_Img2.a(1,0) * latCorrection2.scale * hCorrection2.scale;

    double a2_Img2 =   Coefs_Img2.a(2,0) * longCorrection2.scale * hCorrection2.scale;

    double a3_Img2 =   Coefs_Img2.a(3,0) * longCorrection2.scale * latCorrection2.scale;


    double b0_Img2 =            longCorrection2.scale * latCorrection2.scale * hCorrection2.scale - 
                                Coefs_Img2.b(1,0) * longCorrection2.off * latCorrection2.scale * hCorrection2.scale - 
                                Coefs_Img2.b(2,0) * longCorrection2.scale * latCorrection2.off * hCorrection2.scale -
                                Coefs_Img2.b(3,0) * longCorrection2.scale * latCorrection2.scale * hCorrection2.off;
    
    double b1_Img2 =   Coefs_Img2.b(1,0) * latCorrection2.scale * hCorrection2.scale;

    double b2_Img2 =   Coefs_Img2.b(2,0) * longCorrection2.scale * hCorrection2.scale;

    double b3_Img2 =   Coefs_Img2.b(3,0) * longCorrection2.scale * latCorrection2.scale;



    double c0_Img2 =   Coefs_Img2.c(0,0) * longCorrection2.scale * latCorrection2.scale * hCorrection2.scale - 
                                Coefs_Img2.c(1,0) * longCorrection2.off * latCorrection2.scale * hCorrection2.scale - 
                                Coefs_Img2.c(2,0) * longCorrection2.scale * latCorrection2.off * hCorrection2.scale -
                                Coefs_Img2.c(3,0) * longCorrection2.scale * latCorrection2.scale * hCorrection2.off;
    
    double c1_Img2 =   Coefs_Img2.c(1,0) * latCorrection2.scale * hCorrection2.scale;

    double c2_Img2 =   Coefs_Img2.c(2,0) * longCorrection2.scale * hCorrection2.scale;

    double c3_Img2 =   Coefs_Img2.c(3,0) * longCorrection2.scale * latCorrection2.scale;


    double d0_Img2 =    longCorrection2.scale * latCorrection2.scale * hCorrection2.scale - 
                        Coefs_Img2.d(1,0) * longCorrection2.off * latCorrection2.scale * hCorrection2.scale - 
                        Coefs_Img2.d(2,0) * longCorrection2.scale * latCorrection2.off * hCorrection2.scale -
                        Coefs_Img2.d(3,0) * longCorrection2.scale * latCorrection2.scale * hCorrection2.off;
    
    double d1_Img2 =   Coefs_Img2.d(1,0) * latCorrection2.scale * hCorrection2.scale;

    double d2_Img2 =   Coefs_Img2.d(2,0) * longCorrection2.scale * hCorrection2.scale;

    double d3_Img2 =   Coefs_Img2.d(3,0) * longCorrection2.scale * latCorrection2.scale;

/*
This section does the matrix multiplications as in a iterative method
The purpose is to aproximate initial values through Least Squares, to later ajustment

obs: Static size matrixes were used to optimeze performance.
*/
    Eigen::MatrixXd A;
    Eigen::MatrixXd L;
    Eigen::MatrixXd Xa;
    mmqReturn teste;
    for (int i = 0; i < Line1.rows(); i++)
    {
         A << a1_Img1-l1(i,0)*b1_Img1, a2_Img1-l1(i,0)*b2_Img1, a3_Img1-l1(i,0)*b3_Img1,
              c1_Img1-s1(i,0)*d1_Img1, c2_Img1-s1(i,0)*d2_Img1, c3_Img1-s1(i,0)*d3_Img1,
              a1_Img2-l2(i,0)*b1_Img2, a2_Img2-l2(i,0)*b2_Img2, a3_Img2-l2(i,0)*b3_Img2,
              c1_Img2-s2(i,0)*d1_Img2, c2_Img2-s2(i,0)*d2_Img2, c3_Img2-s2(i,0)*d3_Img2;

        L << l1(i,0)*b0_Img1 - a0_Img1, 
             s1(i,0)*d0_Img1 - c0_Img1,
             l2(i,0)*b0_Img2 - a0_Img2, 
             s2(i,0)*d0_Img2 - c0_Img2;

        teste = mmq(A,L);
        Xa = teste.Xa;
    }
    
    /*
    This section selects indexes of the elements in the Xa matrix 
    that correspond to LONG, LAT and H
    After that, it alocates those in a correspondent matrix
    */

    Eigen::MatrixXd PontosLong(Line1.rows(),1);
    Eigen::MatrixXd PontosLat(Line1.rows(),1);
    Eigen::MatrixXd Pontosh(Line1.rows(),1);
    
    for (int i = 0; i < Line1.rows(); i++){
        PontosLong(i,0) = 3*i-2;
        PontosLat(i,0) = 3*i-1;
        Pontosh(i,0) = 3*i;
    }

    Eigen::MatrixXd Long = Xa(PontosLong,Eigen::all);
    Eigen::MatrixXd Lat = Xa(PontosLat,Eigen::all);
    Eigen::MatrixXd h = Xa(Pontosh,Eigen::all);

    //iterative method
    
    /*
    This section uses B,L,H to represent Geodetic Latitude and Longitude and Geometric Height for both images, respectively
    However, in order to make the code more readable, the abreviations of the coordinates were added.
    */

    for(int i = 0; i<Long.rows();i++){
        for(int j = 0; j<3; j++){
            //Preivous Coordinates Normalization for both images

            double B_Img1 = ElementNormalization(Lat(i,j),latCorrection1.off,latCorrection1.scale);
            double L_Img1 = ElementNormalization(Long(i,j),longCorrection1.off,longCorrection1.scale);
            double H_Img1 = ElementNormalization(h(i,j),hCorrection1.off,hCorrection1.scale);

            double B_Img2 = ElementNormalization(Lat(i,j),latCorrection2.off,latCorrection2.scale);
            double L_Img2 = ElementNormalization(Long(i,j),longCorrection2.off,longCorrection2.scale);
            double H_Img2 = ElementNormalization(h(i,j),hCorrection2.off,hCorrection2.scale);
            
            /*
            Image's Line (l) and Collumn (s) correspondent to 
            this iteration's Ground Coordinates normalized above
            */

            double l_LineImg1 = Polrfm(B_Img1,L_Img1,H_Img1, Coefs_Img1.a) / Polrfm(B_Img1,L_Img1,H_Img1, Coefs_Img1.b);
            double s_CollumnImg1 = Polrfm(B_Img1,L_Img1,H_Img1, Coefs_Img1.c) / Polrfm(B_Img1,L_Img1,H_Img1, Coefs_Img1.d);

            double l_LineImg2 = Polrfm(B_Img2,L_Img2,H_Img2, Coefs_Img2.a) / Polrfm(B_Img2,L_Img2,H_Img2, Coefs_Img2.b);
            double s_CollumnImg2 = Polrfm(B_Img2,L_Img2,H_Img2, Coefs_Img2.c) / Polrfm(B_Img2,L_Img2,H_Img2, Coefs_Img2.d);
        
            /*
            The parameters ajustment is done through a Least Squares
            just like the Initial Aproximation.
            */

            A << Deriv_L(B_Img1, L_Img1, H_Img1, Coefs_Img1.a, Coefs_Img1.b)/longCorrection1.scale, Deriv_B(B_Img1, L_Img1, H_Img1, Coefs_Img1.a, Coefs_Img1.b)/latCorrection1.scale, Deriv_H(B_Img1, L_Img1, H_Img1, Coefs_Img1.a, Coefs_Img1.b)/hCorrection1.scale;
                 Deriv_L(B_Img1, L_Img1, H_Img1, Coefs_Img1.c, Coefs_Img1.d)/longCorrection1.scale, Deriv_B(B_Img1, L_Img1, H_Img1, Coefs_Img1.c, Coefs_Img1.d)/latCorrection1.scale, Deriv_H(B_Img1, L_Img1, H_Img1, Coefs_Img1.c, Coefs_Img1.d)/hCorrection1.scale;
                 Deriv_L(B_Img2, L_Img2, H_Img2, Coefs_Img2.a, Coefs_Img2.b)/longCorrection2.scale, Deriv_B(B_Img2, L_Img2, H_Img2, Coefs_Img2.a, Coefs_Img2.b)/latCorrection2.scale, Deriv_H(B_Img2, L_Img2, H_Img2, Coefs_Img2.a, Coefs_Img2.b)/hCorrection2.scale;
                 Deriv_L(B_Img2, L_Img2, H_Img2, Coefs_Img2.c, Coefs_Img2.d)/longCorrection2.scale, Deriv_B(B_Img2, L_Img2, H_Img2, Coefs_Img2.c, Coefs_Img2.d)/latCorrection2.scale, Deriv_H(B_Img2, L_Img2, H_Img2, Coefs_Img2.c, Coefs_Img2.d)/hCorrection2.scale;

            L << l1(0,0) - l_LineImg1,
                 s1(0,0) - s_CollumnImg1,
                 l2(0,0) - l_LineImg2,
                 s2(0,0) - s_CollumnImg2;
            
            Eigen::MatrixXd X = mmq(A,L).Xa;

            Long(i,0) = Long(i,0) + X(0,0);
            Lat(i,0) = Lat(i,0) + X(1,0);
            h(i,0) = h(i,0) + X(2,0);
        }
    }

    Coordinates SpacialInterssectionReturn;
    SpacialInterssectionReturn.Long = Long;
    SpacialInterssectionReturn.Lat = Lat;
    SpacialInterssectionReturn.Height = h;

    return SpacialInterssectionReturn;
  
}  
