#include <iostream>
#include "../includes/Eigen/Dense"
#include "../sources/Affine.cpp"
// use the function nor with Asserts libraries, if we change this project to CMAKE we will use CTEST probably
// but in the init use this way

// g++ -g -Wall -I ..\includes\Eigen\Eigen .\Affine_tests.cpp -o Affine_tests

int test2()
{
    /* octave tests
    l01:
    9329
    8731
    11716
    8419

    li:
    9327.9
    8730.9
    11714
    8418.3

    s0i:
    9205
    11815
    11676
    9595

    si:
    9205.3
    11814
    11676
    9596.3
    */

    std::cout << std::endl
              << "Test 2 Data" << std::endl;

    // Example using 4 test points
    int test_points = 4;

    Eigen::MatrixXd l0i(test_points, 1);
    l0i(0, 0) = 9329;
    l0i(1, 0) = 8731;
    l0i(2, 0) = 11716;
    l0i(3, 0) = 8419;
    // std::cout << l0i << std::endl;

    Eigen::MatrixXd li(test_points, 1);
    li(0, 0) = 9327.88401895975; // this data is rounded by octave
    li(1, 0) = 8730.917809298648;
    li(2, 0) = 11714.48542271201;
    li(3, 0) = 8418.346892860209;

    Eigen::MatrixXd s0i(test_points, 1);
    s0i(0, 0) = 9205;
    s0i(1, 0) = 11815;
    s0i(2, 0) = 11676;
    s0i(3, 0) = 9595;

    Eigen::MatrixXd si(test_points, 1);
    si(0, 0) = 9205.290534960121; // not rounded data
    si(1, 0) = 11814.00737567279;
    si(2, 0) = 11676.29146147437;
    si(3, 0) = 9596.276226873404;

    // Eigen have an affine, but i dont know how to use kkkk

    AffineReturn XA_V = Affine(li, si, l0i, s0i);
    std::cout << "----------------" << std::endl;

    std::cout << XA_V.Xa << std::endl;
    std::cout << "----------------" << std::endl;

    std::cout << XA_V.V << std::endl;
}

int main()
{
    // Example using 4 test points
    int test_points = 4;

    Eigen::MatrixXd l0i(test_points, 1);
    l0i(0, 0) = 9032;
    l0i(1, 0) = 7529;
    l0i(2, 0) = 7014;
    l0i(3, 0) = 7471;
    // std::cout << l0i << std::endl;

    Eigen::MatrixXd li(test_points, 1);
    li(0, 0) = 9030.4; // this data is rounded by octave
    li(1, 0) = 7527.9;
    li(2, 0) = 7011.4;
    li(3, 0) = 7470.6;

    Eigen::MatrixXd s0i(test_points, 1);
    s0i(0, 0) = 21880;
    s0i(1, 0) = 15318;
    s0i(2, 0) = 11103;
    s0i(3, 0) = 9543;

    Eigen::MatrixXd si(test_points, 1);
    si(0, 0) = 21881.39002628609; // not rounded data
    si(1, 0) = 15317.60551594586;
    si(2, 0) = 11102.40584691316;
    si(3, 0) = 9543.07405042513;

    // Eigen have an affine, but i dont know how to use kkkk

    AffineReturn XA_V = Affine(li, si, l0i, s0i);
    std::cout << "----------------" << std::endl;

    std::cout << XA_V.Xa << std::endl;
    std::cout << "----------------" << std::endl;

    std::cout << XA_V.V << std::endl;

    test2();
    // for this test Xa need to be 6x1 and V 8x1

    return 0;
}