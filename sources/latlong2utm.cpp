// Include libraries and functions
#include "../includes/Eigen/Dense"
#include "structs.h"

// functions
CoordinatesUTM LatLong2UTM(Eigen::MatrixXd LatitutePoints, Eigen::MatrixXd LongitutePoints)
{
    /*
        in this function enter a Nx1 matrices, the N is variable with the points inputs
        that you using in main to test
    */
    const double PI = 3.14159265358979323846; // pi value

    // WGS84 parameters, i dont know what variable means
    double a = 6378137;
    double invf = 298.257223563;
    double b = a * (1 - 1 / invf);

    // changing latitute and longitute to radians
    LatitutePoints = LatitutePoints * (PI / 180);
    LongitutePoints = LongitutePoints * (PI / 180); // its working
    std::cout << LatitutePoints << std::endl;
};