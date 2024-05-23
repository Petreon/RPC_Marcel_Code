// Inlcude Nor
#include <iostream>
#include "../includes/Eigen/Dense"
#include "../sources/Nor.cpp"
// use the function nor with Asserts librarie, if we change this project to CMAKE we will use, CTEST probably
// but in the init use this way

/*
HOW TO COMPILE THIS PROGRAM
COMAND
g++ -g -Wall -I ..\includes\Eigen\Eigen ..\sources\*.cpp .\Nor_tests.cpp -o teste1
maybe this is temporary
*/

int main()
{
    CorrectionValues line,collumn;
    line.off = 1; line.scale = 2;
    collumn.off = 3; collumn.scale = 1;

    CorrectionValues correcao[] = {line,collumn}; 

    ElementNormalization(100, 100, 100); // Nor.cpp function

    Eigen::Matrix<long, 4, 4> mat;

    Eigen::MatrixXd m(2, 2);
    m(0, 0) = 3;
    m(1, 0) = 2.5;
    m(0, 1) = -1;
    m(1, 1) = m(1, 0) + m(0, 1);

    std::cout <<"Matrix pre normalizacao:\n" << m << "\n" << std::endl;

    std::cout <<"Matrix pos normalizacao:\n" <<  ImgNormalization(m,correcao) << "\n" <<std::endl;

    return 0;
}