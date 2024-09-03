#include <iostream>
#include "../includes/Eigen/Dense"
#include "../sources/Polrfm.cpp"

// g++ -g -Wall -I \includes\Eigen\Eigen \sources\* \tests\Polrfm_tests.cpp -o teste1

// values for Ctr-V in octave
/*

*/

int main()
{

    Eigen::MatrixXd B(4, 1);
    B << 0.3517,
        0.48605,
        -0.21233,
        0.40918;

    Eigen::MatrixXd L(4, 1);
    L << -0.17379,
        -0.13192,
        -0.25701,
        -0.56695;

    Eigen::MatrixXd H(4, 1);
    H << -0.60048,
        -0.61324,
        -0.6219,
        -0.59616;

    Eigen::MatrixXd RPC(20, 1);
    RPC << 0.0026527,
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

    Eigen::MatrixXd result = Polrfm(B, L, H, RPC);

    std::cout << result;

    return 0;
}