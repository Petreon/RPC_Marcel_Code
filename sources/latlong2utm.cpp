// Include libraries and functions
#include <cmath>
#include "../includes/Eigen/Dense"
#include "structs.h"

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
    double e2_square = pow(e2, 2);
    // element-wise operation cos in every Matrix element and returning into a Matrix again
    // this only works because we are handling with a Nx1 Vector
    Eigen::MatrixXd cos_latitute = LatitutePoints.array().cos().matrix();
    Eigen::MatrixXd e2_cos_latitute = cos_latitute * e2_square;

    // element-wise multiplication
    Eigen::MatrixXd n = e2_cos_latitute.array() * cos_latitute.array(); // change this variable name
    // doing the square root of every element in the matrix
    n = n.array().sqrt().matrix();

    Eigen::MatrixXd tan_latitude = LatitutePoints.array().tan();

    std::cout << std::endl;
    std::cout << tan_latitude << std::endl;

    double k0 = 0.9996;
    double FE = 500000;
    double FN = 10000000;

    // now doing this operation -> v = a * ones(rows(lat),1) ./ sqrt(1 - e1^2 * ( sin(lat) .* sin(lat) ) );
    double e1_square = pow(e1, 2);
    Eigen::MatrixXd sin_latitute = LatitutePoints.array().sin();
    sin_latitute = sin_latitute.array() * sin_latitute.array();
    sin_latitute = e1_square * sin_latitute;
    sin_latitute = 1 - sin_latitute.array();
    sin_latitute = sin_latitute.array().sqrt();

    // doing ones()...
    Eigen::MatrixXd ones_Matrix = Eigen::MatrixXd::Ones(LatitutePoints.rows(), 1);
    ones_Matrix = a * ones_Matrix;

    Eigen::MatrixXd v = ones_Matrix.array() / sin_latitute.array();

    std::cout << std::endl;
    std::cout << v << std::endl;

    /*
    std::cout << "_______________" << std::endl;
    std::cout << LatitutePoints << std::endl;
    std::cout << "_______________" << std::endl;
    std::cout << LatitutePoints << std::endl;
    */
    return ConvertedValues2UTM;
};
