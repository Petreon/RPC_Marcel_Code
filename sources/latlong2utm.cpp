// Include libraries and functions
#include <cmath>
#include "../includes/Eigen/Dense"
#include "structs.h"

double CalculateA0(double e1_square2, double e1_square4, double e1_square6, double e1_square8)
{
    // doing this operation
    // A0 = 1 - 1/4*e1^2 - 3/64*e1^4 - 5/256*e1^6 - 175/16384*e1^8;
    double A0 = 0;

    A0 = (double)1 - (double)1 / 4 * e1_square2 - (double)3 / 64 * e1_square4 - (double)5 / 256 * e1_square6 - (double)175 / 16384 * e1_square8;

    return A0;
}

double CalculateA2(double e1_square2, double e1_square4, double e1_square6, double e1_square8)
{
    // doing this operation
    // A2 = 3/8*(e1^2+1/4*e1^4+15/128*e1^6-455/4096*e1^8);
    double A2 = (double)3 / (double)8 * (e1_square2 + (double)1 / 4 * e1_square4 + (double)15 / 128 * e1_square6 - (double)455 / 4096 * e1_square8);

    return A2;
}

double CalculateA4(double e1_square2, double e1_square4, double e1_square6, double e1_square8)
{
    // doing this operation (octave)
    //  A4 = 15/256*(e1^4+3/4*e1^6-77/128*e1^8);
    double A4 = (double)15 / (double)256 * (e1_square4 + (double)3 / 4 * e1_square6 - (double)77 / 128 * e1_square8);
    return A4;
}

// functions
CoordinatesUTM LatLong2UTM(Eigen::MatrixXd LatitutePoints, Eigen::MatrixXd LongitutePoints)
{
    /*
        in this function enter a Nx1 matrices, the N is variable with the points inputs
        that you using in main to test
    */
    CoordinatesUTM ConvertedValues2UTM;

    const double PI = 3.14159265358979323846; // pi value

    // WGS84 parameters, i dont know what variable means
    const double a = 6378137;
    const double invf = 298.257223563;
    double b = a * (1 - 1 / invf);
    double a_square = std::pow(a, 2);
    double b_square = std::pow(b, 2);

    double e1 = std::sqrt((a_square - b_square) / a_square); // OK
    double e2 = std::sqrt((a_square - b_square) / b_square); // OK

    // changing latitute and longitute to radians
    LatitutePoints = LatitutePoints * (PI / 180);
    LongitutePoints = LongitutePoints * (PI / 180); // its working

    // transformation parameters operation(octave) -> n = sqrt( e2^2 * cos(lat) .* cos(lat) );
    double e1_square2 = pow(e1, 2);
    double e2_square2 = pow(e2, 2);
    // these 3 are used later
    double e1_square4 = pow(e1, 4);
    double e1_square6 = pow(e1, 6);
    double e1_square8 = pow(e1, 8);
    // element-wise operation cos in every Matrix element and returning into a Matrix again
    // this only works because we are handling with a Nx1 Vector
    Eigen::MatrixXd cos_latitute = LatitutePoints.array().cos().matrix();
    Eigen::MatrixXd e2_cos_latitute = cos_latitute * e2_square2;

    // element-wise multiplication
    Eigen::MatrixXd n = e2_cos_latitute.array() * cos_latitute.array(); // change this variable name
    // doing the square root of every element in the matrix
    n = n.array().sqrt().matrix();

    Eigen::MatrixXd tan_latitude = LatitutePoints.array().tan();

    // std::cout << std::endl;
    // std::cout << tan_latitude << std::endl;

    double k0 = 0.9996;
    double FE = 500000;
    double FN = 10000000;

    // now doing this operation -> v = a * ones(rows(lat),1) ./ sqrt(1 - e1^2 * ( sin(lat) .* sin(lat) ) );
    double e1_square = pow(e1, 2);
    Eigen::MatrixXd sin_latitute = LatitutePoints.array().sin();
    sin_latitute = sin_latitute.array() * sin_latitute.array();
    sin_latitute = e1_square * sin_latitute;
    sin_latitute = 1 - sin_latitute.array();
    sin_latitute = sin_latitute.array().sqrt(); // sin_latitude = v in the octave code

    // doing ones()...
    Eigen::MatrixXd ones_Matrix = Eigen::MatrixXd::Ones(LatitutePoints.rows(), 1);
    ones_Matrix = a * ones_Matrix;

    Eigen::MatrixXd v = ones_Matrix.array() / sin_latitute.array();

    std::cout << std::endl;
    std::cout << v << std::endl;

    // Sarie Coeficients

    double A0 = CalculateA0(e1_square2, e1_square4, e1_square6, e1_square8); // OK Checked
    double A2 = CalculateA2(e1_square2, e1_square4, e1_square6, e1_square8); // OK Checked
    double A4 = CalculateA4(e1_square2, e1_square4, e1_square6, e1_square8);
    /*
    std::cout << "_______________" << std::endl;
    std::cout << LatitutePoints << std::endl;
    std::cout << "_______________" << std::endl;
    std::cout << LatitutePoints << std::endl;
    */
    return ConvertedValues2UTM;
};
