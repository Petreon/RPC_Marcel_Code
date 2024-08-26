#include <iostream>
#include "../includes/Eigen/Dense"
#include "../sources/Deriv_H.cpp"

// g++ -g -Wall -I \includes\Eigen\Eigen \sources\* \tests\Deriv_H_tests.cpp -o teste1

// values for Ctr-V in octave
/*
rpc_den:
1
-0.00029895
7.8954e-05
-0.00011749
8.8042e-06
-2.5021e-07
1.5545e-06
1.2371e-05
-4.2816e-05
1.5044e-05
3.2624e-06
-1.9417e-07
-0.00013771
-1.5076e-08
8.8821e-06
0.00071074
4.4228e-08
-9.8385e-08
-2.5394e-05
-1.166e-08

rpc_num:
0.0026527
0.065984
-1.0491
0.01717
-0.00011533
1.2125e-05
-8.0481e-05
0.0001155
-0.0024174
7.8213e-07
-2.326e-07
7.1203e-07
6.4664e-06
9.9747e-07
-1.1069e-05
-6.3261e-05
-1.5919e-05
1.9767e-07
2.3314e-06
2.8088e-07
*/

int main()
{
    // test examples
    double B = 0.4930997518530623;
    double H = 0.07621875800192356;
    double L = -0.1912648085899932;

    Eigen::MatrixXd rpc_num(20, 1);
    rpc_num << 0.0026527,
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

    Eigen::MatrixXd rpc_den(20, 1);
    rpc_den << 1,
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

    double result = Deriv_H(B, H, L, rpc_num, rpc_den);
    double octave_result = 0.0172587132903387;
    std::cout << result;
    double relative_error = result - octave_result;
    relative_error = relative_error / octave_result;
    relative_error = relative_error * 100;
}