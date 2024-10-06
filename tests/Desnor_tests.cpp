// Inlcude Nor
#include <iostream>
#include "../includes/Eigen/Dense"
#include "Desnor.hpp"
#include "Nor.hpp"
// use the function nor with Asserts librarie, if we change this project to CMAKE we will use, CTEST probably
// but in the init use this way

/*
HOW TO COMPILE THIS PROGRAM
COMAND
g++ -g -Wall -I ..\includes\Eigen\Eigen  .\Desnor_tests.cpp -o teste1
maybe this is temporary
*/

int main()
{
    CorrectionValues line, collumn;
    line.off = 1;
    line.scale = 2;
    collumn.off = 3;
    collumn.scale = 1;

    CorrectionValues correcao[] = {line, collumn};

    ElementNormalization(100, 100, 100); // Nor.cpp function

    Eigen::Matrix<double, 4, 4> mat;
    mat(0, 0) = 4;
    mat(1, 0) = 3;
    mat(0, 1) = -2;
    mat(1, 1) = -1;

    std::cout << "Matrix pre normalizacao:\n"
              << mat << "\n"
              << std::endl;

    std::cout << "Matrix pos normalizacao:\n"
              << Normalization(mat, correcao) << "\n"
              << std::endl;

    Eigen::MatrixXd NormalizedMatrix = Normalization(mat, correcao);
    std::cout << "Matrix pos normalizacao:\n"
              << ImgDesnormalization(NormalizedMatrix, correcao) << "\n"
              << std::endl;

    return 0;
}