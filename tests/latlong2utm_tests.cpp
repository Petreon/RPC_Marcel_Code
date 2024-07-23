#include <iostream>
#include "../includes/Eigen/Dense"
#include "../sources/latlong2utm.cpp"
// use the function nor with Asserts libraries, if we change this project to CMAKE we will use CTEST probably
// but in the init use this way

// g++ -g -Wall -I ..\includes\Eigen\Eigen .\latlong2utm_tests.cpp -o latlong2utm_tests
// values for testing
/* lat
-22.914
-22.985
-22.913
-22.924
*/
/* long
-43.206
-43.198
-43.227
-43.236
*/

int main()
{
    Eigen::MatrixXd latitute(4, 1);
    latitute << -22.914,
        -22.985,
        -22.913,
        -22.924;

    Eigen::MatrixXd longitute(4, 1);
    longitute << -43.206,
        -43.198,
        -43.227,
        -43.236;

    // std::cout << latitute << std::endl;
    // std::cout << "_______________" << std::endl;
    // std::cout << longitute << std::endl;
    // std::cout << "_______________" << std::endl;

    CoordinatesUTM coordinatesConverted = LatLong2UTM(latitute, longitute);
    return 0;
}