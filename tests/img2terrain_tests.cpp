#include <iostream>
#include "../includes/Eigen/Dense"
#include "Nor.hpp"
#include "Polrfm.hpp"
#include "Deriv_H.hpp"
#include "Deriv_B.hpp"
#include "Deriv_L.hpp"
#include "Lms.hpp"
#include "img2terrain.hpp"
// Function to test
//Coordinates SpacialInterssection(Coeficients Coefs_Img1, Coeficients Coefs_Img2, Eigen::MatrixXd Line1, Eigen::MatrixXd Sample1, Eigen::MatrixXd Line2, Eigen::MatrixXd Sample2, CorrectionValues l1Correction, CorrectionValues s1Correction, CorrectionValues l2Correction, CorrectionValues s2Correction, CorrectionValues latCorrection1, CorrectionValues longCorrection1, CorrectionValues hCorrection1, CorrectionValues latCorrection2, CorrectionValues longCorrection2, CorrectionValues hCorrection2);

int main() {
    // Mock data for testing
     Coeficients Coefs_Img1, Coefs_Img2;
    Coefs_Img1.a << 0.0026527,
                    0.065984,
                    -1.0491,
                    0.01717,
                    -0.00011533,
                    1.2125e-05,
                    -8.0481e-05,
                    0.0001155,
                    -0.0024174,
                    7.8213e-07,
                    -2.326e-07,
                    7.1203e-07,
                    6.4664e-06,
                    9.9747e-07,
                    -1.1069e-05,
                    -6.3261e-05,
                    -1.5919e-05,
                    1.9767e-07,
                    2.3314e-06,
                    2.8088e-07;

    Coefs_Img1.b << 1,
                    -0.00029895,
                    7.8954e-05,
                    -0.00011749,
                    8.8042e-06,
                    -2.5021e-07,
                    1.5545e-06,
                    1.2371e-05,
                    -4.2816e-05,
                    1.5044e-05,
                    3.2624e-06,
                    -1.9417e-07,
                    -0.00013771,
                    -1.5076e-08,
                    8.8821e-06,
                    0.00071074,
                    4.4228e-08,
                    -9.8385e-08,
                    -2.5394e-05,
                    -1.166e-08;

    Coefs_Img1.c << -0.0033986,
                    0.9897,
                    -0.00085968,
                    -0.012103,
                    0.00050019,
                    0.00031143,
                    -0.00010604,
                    0.002964,
                    -1.9988e-06,
                    -1.4262e-06,
                    -3.7614e-07,
                    -5.2881e-08,
                    -1.981e-05,
                    -3.8614e-06,
                    2.0466e-05,
                    0.00010358,
                    -1.4172e-08,
                    1.5394e-06,
                    -2.8808e-06,
                    1.0246e-07;

    Coefs_Img1.d << 1,
                    0.00043431,
                    -0.00049872,
                    -0.00034948,
                    -6.0159e-06,
                    -9.9386e-07,
                    -2.2246e-07,
                    2.2275e-06,
                    1.6616e-05,
                    -4.0906e-06,
                    -2.8678e-08,
                    4.1108e-08,
                    0,
                    0,
                    -1.0766e-07,
                    0,
                    0,
                    0,
                    0,
                    0;

    Coefs_Img2.a << 0.0034686,
                    0.0032614,
                    -0.99579,
                    0.0090291,
                    -0.00040421,
                    5.6939e-06,
                    -0.0005673,
                    0.00016516,
                    -0.0026356,
                    4.1737e-06,
                    -7.8582e-07,
                    -2.578e-07,
                    2.0168e-05,
                    -4.1006e-07,
                    0.0001027,
                    0.00045642,
                    0.00012645,
                    -8.3041e-07,
                    -1.3302e-05,
                    -1.1132e-06;

    Coefs_Img2.b << 1,
                    -0.00041495,
                    0.0012677,
                    -0.00060999,
                    1.0554e-05,
                    -6.5078e-07,
                    -7.3453e-06,
                    -8.9957e-05,
                    0.00028159,
                    -0.00012755,
                    -8.7447e-08,
                    6.7268e-08,
                    1.6249e-05,
                    9.932e-08,
                    6.7376e-08,
                    -0.0015066,
                    4.4366e-07,
                    1.3615e-07,
                    2.3403e-05,
                    1.1574e-07;

    Coefs_Img2.c << -0.0010631,
                    1.003,
                    -0.00041582,
                    -0.0015422,
                    0.0018211,
                    0.0003465,
                    0.00011893,
                    0.0006761,
                    -6.626e-05,
                    -1.4849e-06,
                    4.0979e-06,
                    -3.0294e-05,
                    -0.00010809,
                    -2.0216e-05,
                    -1.5045e-05,
                    -8.6779e-05,
                    1.745e-07,
                    6.7501e-07,
                    1.3046e-06,
                    2.1773e-08;
                    
    Coefs_Img2.d << 1,
                    0.00038937,
                    -0.0018268,
                    -0.00034919,
                    2.206e-06,
                    -7.7735e-08,
                    -3.1329e-06,
                    -2.2527e-05,
                    8.49e-05,
                    -2.0319e-05,
                    2.1582e-08,
                    1.8369e-08,
                    5.6151e-07,
                    0,
                    1.0315e-07,
                    2.9291e-06,
                    6.3225e-08,
                    4.299e-08,
                    3.9622e-07,
                    0;

    Eigen::MatrixXd Line1;
    Eigen::MatrixXd Sample1;
    Eigen::MatrixXd Line2;
    Eigen::MatrixXd Sample2;
    
    Line1 << 7529,
             23398,
             9329,
             8564;
  
    Line2 << 8958,
             24855,
             11148,
             9483;

    Sample1 << 15318,
               19103,
               9205,
               24192;
    
    Sample2 << 9293,
               13129,
               3118,
               18251;
               
    CorrectionValues l1Correction = {16506,16225};
    CorrectionValues s1Correction = {17808, 17577};
    CorrectionValues l2Correction = {17419, 17282};
    CorrectionValues s2Correction = {16571, 16531};
    CorrectionValues latCorrection1 = {0.080600, -22.953};
    CorrectionValues longCorrection1 = {0.087300, -43.194};
    CorrectionValues hCorrection1 = {500, 307};
    CorrectionValues latCorrection2 = {0.079400, -22.952};
    CorrectionValues longCorrection2 = {0.081600, -43.170};
    CorrectionValues hCorrection2 = {500, 225};

    // Call the function to test
    Coordinates result = SpacialInterssection(Coefs_Img1, Coefs_Img2, Line1, Sample1, Line2, Sample2, l1Correction, s1Correction, l2Correction, s2Correction, latCorrection1, longCorrection1, hCorrection1, latCorrection2, longCorrection2, hCorrection2);

    // Print the results
    std::cout << "Longitude:\n" << result.Long << "\n";
    std::cout << "Latitude:\n" << result.Lat << "\n";
    std::cout << "Height:\n" << result.Height << "\n";

    return 0;
}