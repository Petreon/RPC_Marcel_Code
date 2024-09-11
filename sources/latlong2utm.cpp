// Include libraries and functions
#include <cmath>
#include <iomanip>
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
    Lat_points_2sen = Lat_points_2sen.array().sin();
    // std::cout << Lat_points_2sen << std::endl;
    Eigen::MatrixXd Lat_points_4sen = 4 * LatitutePoints;
    Lat_points_4sen = Lat_points_4sen.array().sin();

    Eigen::MatrixXd Lat_points_6sen = 6 * LatitutePoints;
    Lat_points_6sen = Lat_points_6sen.array().sin();

    Eigen::MatrixXd Lat_points_8sen = 8 * LatitutePoints;
    Lat_points_8sen = Lat_points_8sen.array().sin();

    B = a_value * (A0 * LatitutePoints - A2 * Lat_points_2sen + A4 * Lat_points_4sen - A6 * Lat_points_6sen + A8 * Lat_points_8sen);

    // std::cout << "_____________" << std::endl;
    // std::cout << B << std::endl;
    return B;
}

Eigen::MatrixXd CalculateCentralMeridian(Eigen::MatrixXd F, const double PI)
{
    // Central Meridian Calculus
    //  long0 = 6 * ( pi / 180) / 2 * ( 2 * ( F - ( pi / ( 6 * (pi / 180) ) ) ) - 1);
    Eigen::MatrixXd Long_0 = (double)6 * (PI / (double)180) / (double)2 * ((double)2 * (F.array() - (PI / ((double)6 * (PI / (double)180)))) - (double)1);
    // std::cout << Long_0 << std::endl;
    return Long_0;
}

Eigen::MatrixXd CalculateElp2(Eigen::MatrixXd v, Eigen::MatrixXd d_long, Eigen::MatrixXd cos_lat, Eigen::MatrixXd tan_lat, Eigen::MatrixXd n)
{
    /* Doing this operation (octave), this is a full element-wise operation so v[1] communicates with d_long[1] and so on.
    Elp2 = v.*dlong.^3 .* (cos(lat).^3).*(1 - t.^2 + n.^2)/6;

    x.array() * y.array() are element-wise operations
    */
    Eigen::MatrixXd Elp2 = v.array() * d_long.array().pow(3) * (cos_lat.array().pow(3)) * ((double)1 - tan_lat.array().pow(2) + n.array().pow(2)) / (double)6;
    // std::cout << "Elp2 result :" << std::endl;
    // std::cout << Elp2 << std::endl;
    return Elp2;
}

Eigen::MatrixXd CalculateElp3(Eigen::MatrixXd v, Eigen::MatrixXd d_long, Eigen::MatrixXd cos_lat, Eigen::MatrixXd tan_lat, Eigen::MatrixXd n)
{
    /* Doing this operation (octave), this is a full element-wise operation so v[1] communicates with d_long[1] and so on.
    Elp2 = v .* dlong.^5 .* (cos(lat).^5).*(5 - 18*t.^2 + t.^4 + 14*n.^2 - 58*n.^2 .*t.^2 + 13*n.^4 + 4*n.^6 - 64*n.^4.*t.^2 - 24*n.^6.*t.^2)/120;

    x.array() * y.array() are element-wise operations
    */
    Eigen::MatrixXd Elp3 = v.array() * d_long.array().pow(5) * (cos_lat.array().pow(5)) * ((double)5 - (double)18 * tan_lat.array().pow(2) + tan_lat.array().pow(4) + (double)14 * n.array().pow(2) - (double)58 * n.array().pow(2) * tan_lat.array().pow(2) + (double)13 * n.array().pow(4) + (double)4 * n.array().pow(6) - (double)64 * n.array().pow(4) * tan_lat.array().pow(2) - (double)24 * n.array().pow(6) * tan_lat.array().pow(2)) / (double)120;
    // std::cout << "Elp3 result :" << std::endl;
    // std::cout << Elp3 << std::endl;
    return Elp3;
}

Eigen::MatrixXd CalculateElp4(Eigen::MatrixXd v, Eigen::MatrixXd d_long, Eigen::MatrixXd cos_lat, Eigen::MatrixXd tan_lat, Eigen::MatrixXd n)
{
    /* Doing this operation (octave) (octave), this is a full element-wise operation so v[1] communicates with d_long[1] and so on.
    Elp2 = v.*dlong.^7 .*(cos(lat).^7).*(61 - 479*t.^2 + 179*t.^4 - t.^6)/5040;
    x.array() * y.array() are element-wise operations
    */
    Eigen::MatrixXd Elp4 = v.array() * d_long.array().pow(7) * (cos_lat.array().pow(7)) * ((double)61 - (double)479 * tan_lat.array().pow(2) + (double)179 * tan_lat.array().pow(4) - tan_lat.array().pow(6)) / (double)5040;
    // std::cout << "Elp4 result :" << std::endl;
    // std::cout << Elp4 << std::endl;
    return Elp4;
}

Eigen::MatrixXd CalculateNlp2(Eigen::MatrixXd v, Eigen::MatrixXd d_long, Eigen::MatrixXd cos_lat, Eigen::MatrixXd sin_lat, Eigen::MatrixXd tan_lat, Eigen::MatrixXd n)
{
    /* Doing this operation (octave) , this is a full element-wise operation so v[1] communicates with d_long[1] and so on.
    Nlp2 = v.*dlong.^2.*sin(lat).*cos(lat)/2;
    x.array() * y.array() are element-wise operations
    */

    Eigen::MatrixXd Nlp2 = v.array() * d_long.array().pow(2) * sin_lat.array() * cos_lat.array() / 2;
    // std::cout << "Nlp2 Test: " << std::endl;
    // std::cout << Nlp2 << std::endl;
    return Nlp2;
}

Eigen::MatrixXd CalculateNlp3(Eigen::MatrixXd v, Eigen::MatrixXd d_long, Eigen::MatrixXd cos_lat, Eigen::MatrixXd sin_lat, Eigen::MatrixXd tan_lat, Eigen::MatrixXd n)
{
    /* Doing this operation (octave) , this is a full element-wise operation so v[1] communicates with d_long[1] and so on.
    Nlp3 = v.*dlong.^4.*sin(lat).*(cos(lat).^3).*(5-t.^2+9*n.^2+4*n.^4)/24;
    x.array() * y.array() are element-wise operations
    */

    Eigen::MatrixXd Nlp3 = v.array() * d_long.array().pow(4) * sin_lat.array() * (cos_lat.array().pow(3)) * ((double)5 - tan_lat.array().pow(2) + (double)9 * n.array().pow(2) + (double)4 * n.array().pow(4)) / (double)24;
    // std::cout << "Nlp3 Test: " << std::endl;
    // std::cout << Nlp3 << std::endl;
    return Nlp3;
}

Eigen::MatrixXd CalculateNlp4(Eigen::MatrixXd v, Eigen::MatrixXd d_long, Eigen::MatrixXd cos_lat, Eigen::MatrixXd sin_lat, Eigen::MatrixXd tan_lat, Eigen::MatrixXd n)
{
    /* Doing this operation (octave) , this is a full element-wise operation so v[1] communicates with d_long[1] and so on.
    Nlp4 = v.*dlong.^6 .* sin(lat).*(cos(lat).^5).*(61 - 58*t.^2 + t.^4 + 270*n.^2 - 330*n.^2.*t.^2 + 445*n.^4 + 324*n.^6 - 680*n.^4.*t.^2 + 88*n.^8 - 600*n.^6.*t.^2 - 192*n.^8.*t.^2)/720;
    x.array() * y.array() are element-wise operations
    */

    Eigen::MatrixXd Nlp4 = v.array() * d_long.array().pow(6) * sin_lat.array() * (cos_lat.array().pow(5)) * ((double)61 - (double)58 * tan_lat.array().pow(2) + tan_lat.array().pow(4) + (double)270 * n.array().pow(2) - (double)330 * n.array().pow(2) * tan_lat.array().pow(2) + (double)445 * n.array().pow(4) + (double)324 * n.array().pow(6) - (double)680 * n.array().pow(4) * tan_lat.array().pow(2) + (double)88 * n.array().pow(8) - (double)600 * n.array().pow(6) * tan_lat.array().pow(2) - (double)192 * n.array().pow(8) * tan_lat.array().pow(2)) / (double)720;

    // std::cout << "Nlp4 Test: " << std::endl;
    // std::cout << Nlp4 << std::endl;

    return Nlp4;
}

Eigen::MatrixXd CalculateNlp5(Eigen::MatrixXd v, Eigen::MatrixXd d_long, Eigen::MatrixXd cos_lat, Eigen::MatrixXd sin_lat, Eigen::MatrixXd tan_lat, Eigen::MatrixXd n)
{
    /* Doing this operation (octave) , this is a full element-wise operation so v[1] communicates with d_long[1] and so on.
   Nlp5 = v.*dlong.^8.*sin(lat).*(cos(lat).^7).*(1385-3111*t.^2+543*t.^4-t.^6)/40320;
   x.array() * y.array() are element-wise operations
   */

    Eigen::MatrixXd Nlp5 = v.array() * d_long.array().pow(8) * sin_lat.array() * (cos_lat.array().pow(7)) * ((double)1385 - (double)3111 * tan_lat.array().pow(2) + (double)543 * tan_lat.array().pow(4) - tan_lat.array().pow(6)) / (double)40320;

    // std::cout << "Nlp5 Test: " << std::endl;
    // std::cout << Nlp5 << std::endl;

    return Nlp5;
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
    Eigen::MatrixXd sin_latitute_forV = LatitutePoints.array().sin();
    sin_latitute_forV = sin_latitute_forV.array() * sin_latitute_forV.array();
    sin_latitute_forV = e1_square * sin_latitute_forV;
    sin_latitute_forV = 1 - sin_latitute_forV.array();
    sin_latitute_forV = sin_latitute_forV.array().sqrt();

    // doing ones()...
    Eigen::MatrixXd ones_Matrix = Eigen::MatrixXd::Ones(LatitutePoints.rows(), 1);
    ones_Matrix = a * ones_Matrix;

    // what is this V matrix?
    Eigen::MatrixXd v = ones_Matrix.array() / sin_latitute_forV.array();

    // std::cout << std::endl;
    // std::cout << v << std::endl;

    // Serie Coeficients, fourier?

    double A0 = CalculateA0(e1_square2, e1_square4, e1_square6, e1_square8); // OK Checked
    double A2 = CalculateA2(e1_square2, e1_square4, e1_square6, e1_square8); // OK Checked
    double A4 = CalculateA4(e1_square2, e1_square4, e1_square6, e1_square8); // OK Checked
    double A6 = CalculateA6(e1_square6, e1_square8);                         // OK checked
    double A8 = CalculateA8(e1_square8);                                     // OK checked

    // Calculate B
    Eigen::MatrixXd B = CalculateB(LatitutePoints, a, A0, A2, A4, A6, A8); // OK checked

    // Calculating F (Fuse), why it round the numbers?
    // doing these operations
    // F = pi/(6*(pi/180)) + fix(long/(6*(pi/180)));
    Eigen::MatrixXd Longitute_points_round = LongitutePoints / ((double)6 * (PI / (double)180));
    Longitute_points_round = Longitute_points_round.array().round();

    // element-wise operation
    Eigen::MatrixXd F = PI / ((double)6 * (PI / 180)) + Longitute_points_round.array(); // checked OK
    // std::cout << F << std::endl; //checked OK

    // Central Meridian Calculus
    //  long0 = 6 * ( pi / 180) / 2 * ( 2 * ( F - ( pi / ( 6 * (pi / 180) ) ) ) - 1);
    Eigen::MatrixXd Long_0 = CalculateCentralMeridian(F, PI); // OK Checked

    // longitute diference
    Eigen::MatrixXd D_Long = LongitutePoints - Long_0; // OK checked
    // std::cout << D_Long << std::endl;

    // Elp's Calculos and Nlp's, E' and N'
    // element-wise operations not matrices
    Eigen::MatrixXd Elp1 = v.array() * D_Long.array() * cos_latitute.array();       // OK checked
    Eigen::MatrixXd Elp2 = CalculateElp2(v, D_Long, cos_latitute, tan_latitude, n); // OK checked
    Eigen::MatrixXd Elp3 = CalculateElp3(v, D_Long, cos_latitute, tan_latitude, n); // OK checked
    Eigen::MatrixXd Elp4 = CalculateElp4(v, D_Long, cos_latitute, tan_latitude, n); // OK checked
    Eigen::MatrixXd El = Elp1 + Elp2 + Elp3 + Elp4;                                 // OK checked
    // std::cout << "El Result: " << std::endl;
    //  std::cout << std::fixed << std::setprecision(8); // only to show the whole value
    // std::cout << El.row(1) << std::endl; OK CHECKED
    Eigen::MatrixXd sin_latitute = LatitutePoints.array().sin();

    Eigen::MatrixXd Nlp1 = B;                                                                     // OK CHECKED
    Eigen::MatrixXd Nlp2 = CalculateNlp2(v, D_Long, cos_latitute, sin_latitute, tan_latitude, n); // OK CHECKED
    Eigen::MatrixXd Nlp3 = CalculateNlp3(v, D_Long, cos_latitute, sin_latitute, tan_latitude, n); // OK CHECKED
    Eigen::MatrixXd Nlp4 = CalculateNlp4(v, D_Long, cos_latitute, sin_latitute, tan_latitude, n); // OK CHECKED
    Eigen::MatrixXd Nlp5 = CalculateNlp5(v, D_Long, cos_latitute, sin_latitute, tan_latitude, n); // OK CHECKED
    Eigen::MatrixXd Nl = Nlp1 + Nlp2 + Nlp3 + Nlp4 + Nlp5;                                        // OK CHECKED

    // std::cout << "Nl values:" << std::endl;
    // std::cout << std::fixed << std::setprecision(8);
    // std::cout << Nl << std::endl;
    Eigen::MatrixXd E = El * k0;
    E = FE + E.array(); // OK CHECKED
    Eigen::MatrixXd N = Nl * k0;
    N = FN + N.array();

    ConvertedValues2UTM.East = E;
    ConvertedValues2UTM.North = N;
    ConvertedValues2UTM.Fuse = F;

    return ConvertedValues2UTM;
};
