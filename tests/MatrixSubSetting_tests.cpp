#include <iostream>
#include "../includes/Eigen/Dense"
#include "MatrixSubSetting.hpp"

int main(){

    Eigen::MatrixXd MatrixTest(18,1);
    for(int i = 0; i < MatrixTest.rows(); i++){

        MatrixTest(i,0) = i+10;
    }

    Eigen::MatrixXd IndexTest(1,4);
    IndexTest(0,0) = 3;
    IndexTest(0,1) = 7;
    IndexTest(0,2) = 1;
    IndexTest(0,3) = 9;

    Eigen::MatrixXd newMatrix = MatrixSubSetting(MatrixTest,IndexTest);

    std::cout << newMatrix << std::endl;

    return 0;
}