#include "../includes/Eigen/Dense"
#include <iostream>
#include "structs.hpp"

// what is this operation?
mmqReturn mmq(Eigen::MatrixXd A, Eigen::MatrixXd L)
{
    /*I dont know the objective of this function but do this operations*/
    // this function is ready
    mmqReturn ObjReturned;

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