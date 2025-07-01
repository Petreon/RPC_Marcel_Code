#include "../includes/Eigen/Dense"
#include <iostream>
#include "Lms.hpp"


LmsReturn LeastMinSquare(Eigen::MatrixXd A, Eigen::MatrixXd L)
{
    // this function calculates the Least Minimum Square
    // this function is ready
    LmsReturn ObjReturned;

    // doing this operations in octave Xa = inv(A'*A)*A'*L;
    Eigen::MatrixXd ATA = (A.transpose() * A);
    Eigen::MatrixXd ATA_inverse = ATA.inverse();

    Eigen::MatrixXd Xa = ATA_inverse * A.transpose() * L;
    ObjReturned.Xa = Xa;

    Eigen::MatrixXd V = (A * Xa) - L;
    ObjReturned.V = V;

    // std::cout << V << std::endl;
    return ObjReturned;
}