#include <iostream>
#include "../includes/Eigen/Dense"
#include "Lms.hpp"
// use the function nor with Asserts libraries, if we change this project to CMAKE we will use CTEST probably
// but in the init use this way

// g++ -g -Wall -I ..\includes\Eigen\Eigen ..\sources\*.cpp .\Lms_tests.cpp -o Lms_tests

int main()
{
    // test matrizes using a test for a 4 points only these points are best defined in Affine_tests
    Eigen::MatrixXd A(8, 6);
    A << 1, 9030.4, 21881.4, 0, 0, 0,
        1, 7527.9, 15317.6, 0, 0, 0,
        1, 7011.4, 11102.4, 0, 0, 0,
        1, 7470.6, 9543.07, 0, 0, 0,
        0, 0, 0, 1, 9030.4, 21881.4,
        0, 0, 0, 1, 7527.9, 15317.6,
        0, 0, 0, 1, 7011.4, 11102.4,
        0, 0, 0, 1, 7470.6, 9543.07;

    // a 8x1 matrix to do the calculos for
    Eigen::MatrixXd L(8, 1);
    L << -1.6,
        -1.1,
        -2.6,
        -0.4,
        1.39003,
        -0.394484,
        -0.594153,
        0.0740504;

    LmsReturn XA_V_Matrixes = LeastMinSquare(A, L);

    std::cout << XA_V_Matrixes.Xa << std::endl;

    return 0;
}