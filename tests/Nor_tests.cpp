// Inlcude Nor
#include <iostream>
#include "../includes/Eigen/Dense"
#include "../sources/Nor.cpp"
// use the function nor with Asserts librarie, if we change this project to CMAKE we will use, CTEST probably
// but in the init use this way

using Eigen::MatrixXd;

/*
HOW TO COMPILE THIS PROGRAM
COMAND
g++ -g -Wall -I ..\includes\Eigen\Eigen ..\sources\*.cpp .\Nor_tests.cpp -o teste1
maybe this is temporary
*/

int main()
{
    Normalization(); // Nor.cpp function

    Eigen::Matrix<double, 4, 4> mat;

    MatrixXd m(2, 2);
    m(0, 0) = 3;
    m(1, 0) = 2.5;
    m(0, 1) = -1;
    m(1, 1) = m(1, 0) + m(0, 1);
    std::cout << m << std::endl;

    return 0;
}