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

double CalculateA6(double e1_square6, double e1_square8)
{
    // doing this operation
    //  35 / 3072 * ( e1^6-41 / 32*e1^8 ) ;
    double A6 = 0;
    A6 = (double)35 / 3072 * (e1_square6 - (double)41 / 32 * e1_square8);
    return A6;
}

double CalculateA8(double e1_square8)
{
    // doing this operation
    //  -315/131072*e1^8;
    double A8 = 0;
    A8 = (double)-315 / 131072 * e1_square8;
    return A8;
}

Eigen::MatrixXd CalculateB(Eigen::MatrixXd LatitutePoints, double a_value, double A0, double A2, double A4, double A6, double A8)
{
    // doing this operation (octave)
    // B = a*(A0*lat - A2*sin(2*lat) + A4*sin(4*lat) - A6*sin(6*lat) + A8*sin(8*lat));
    Eigen::MatrixXd B;

    Eigen::MatrixXd Lat_points_2sen = 2 * LatitutePoints;
    // std::cout << Lat_points_2sen << std::endl;
    Lat_points_2sen = LatitutePoints.array().sin();
    // std::cout << Lat_points_2sen << std::endl;
    Eigen::MatrixXd Lat_points_4sen = 4 * LatitutePoints;
    Lat_points_2sen = LatitutePoints.array().sin();

    Eigen::MatrixXd Lat_points_6sen = 6 * LatitutePoints;
    Lat_points_2sen = LatitutePoints.array().sin();

    Eigen::MatrixXd Lat_points_8sen = 8 * LatitutePoints;
    Lat_points_2sen = LatitutePoints.array().sin();

    // ATTENTION, CALCULOS DOENST FIT HERE, the result in octave was
    //-2.535e+06
    //-2.5429e+06
    //-2.5349e+06
    //-2.5361e+06
    // and he is almost sum 0.07 above like -2.54028e+06
    B = a_value * (A0 * LatitutePoints - A2 * Lat_points_2sen + A4 * Lat_points_4sen - A6 * Lat_points_6sen + A8 * Lat_points_8sen);

    // std::cout << "_____________" << std::endl;
    // std::cout << B << std::endl;
    return B;
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
    LatitutePoints = LatitutePoints * (PI / 180);   // lat variable
    LongitutePoints = LongitutePoints * (PI / 180); // its working , long variable

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
    double A4 = CalculateA4(e1_square2, e1_square4, e1_square6, e1_square8); // OK Checked
    double A6 = CalculateA6(e1_square6, e1_square8);                         // OK checked
    double A8 = CalculateA8(e1_square8);                                     // OK checked

    // Calculate B
    Eigen::MatrixXd B = CalculateB(LatitutePoints, a, A0, A2, A4, A6, A8);

    // Calculating F (Fuse), why it round the numbers?
    // doing these operations
    // F = pi/(6*(pi/180)) + fix(long/(6*(pi/180)));
    Eigen::MatrixXd Longitute_points_round = LongitutePoints / (6 * (PI / (double)180));
    Longitute_points_round = Longitute_points_round.array().round();

    // element-wise operation
    Eigen::MatrixXd F = PI / (6 * (PI / 180)) + Longitute_points_round.array();
    // std::cout << F << std::endl; //checked OK

    /*
    std::cout << "_______________" << std::endl;
    std::cout << LatitutePoints << std::endl;
    std::cout << "_______________" << std::endl;
    std::cout << LatitutePoints << std::endl;
    */
    return ConvertedValues2UTM;
};
