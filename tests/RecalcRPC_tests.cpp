#include "../includes/Eigen/Dense"
#include "../sources/RecalcRPC.cpp"
#include <iostream>

/*
Input Bn, Hn, Ln octave code for debug
Bn:
-0.2928
0.46897
0.36081
0.48605

Hn:
-0.6163
-0.60587
-0.59636
-0.61324

Ln:
0.0031803
-0.45996
-0.47919
-0.13192

LineMeas:
21165
7471
9329
7529

SampleMeas:
21165
7471
9329
7529

*/

int main()
{
    Eigen::MatrixXd Bn(4, 1);
    Bn << -0.2928,
        0.46897,
        0.36081,
        0.48605;

    Eigen::MatrixXd Hn(4, 1);
    Hn << -0.6163,
        -0.60587,
        -0.59636,
        -0.61324;

    Eigen::MatrixXd Ln(4, 1);
    Ln << 0.0031803,
        -0.45996,
        -0.47919,
        -0.13192;

    Eigen::MatrixXd LineMeas(4, 1);
    LineMeas << 21165,
        7471,
        9329,
        7529;

    Eigen::MatrixXd SampleMeas(4, 1);
    SampleMeas << 21165,
        7471,
        9329,
        7529;

    Eigen::MatrixXd rpc_dl(20, 1);
    rpc_dl << 1, -0.00029895,
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

    Eigen::MatrixXd rpc_ds(20, 1);
    rpc_ds << 1, -0.00029895,
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

    Eigen::MatrixXd rpc_nl(20, 1);
    rpc_nl << 0.0026527,
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

    Eigen::MatrixXd rpc_ns(20, 1);
    rpc_ns << -0.0033986,
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

    double Line_Off = 16225;
    double Line_Scale = 16506;
    double Sample_Off = 17577;
    double Sample_Scale = 17808;

    RecalcReturn result = RecalcRPC(Bn, Ln, Hn, rpc_nl, rpc_dl, rpc_ns, rpc_ds, LineMeas, SampleMeas, Line_Off, Line_Scale, Sample_Off, Sample_Scale);

    std::cout << "Aloo";
}