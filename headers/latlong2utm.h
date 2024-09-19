#pragma once
#include "../sources/structs.h"

double CalculateA0(double e1_square2, double e1_square4, double e1_square6, double e1_square8);
double CalculateA2(double e1_square2, double e1_square4, double e1_square6, double e1_square8);
double CalculateA4(double e1_square2, double e1_square4, double e1_square6, double e1_square8);
double CalculateA6(double e1_square6, double e1_square8);
double CalculateA8(double e1_square8);
Eigen::MatrixXd CalculateB(Eigen::MatrixXd LatitutePoints, double a_value, double A0, double A2, double A4, double A6, double A8);
Eigen::MatrixXd CalculateCentralMeridian(Eigen::MatrixXd F, const double PI);
Eigen::MatrixXd CalculateElp2(Eigen::MatrixXd v, Eigen::MatrixXd d_long, Eigen::MatrixXd cos_lat, Eigen::MatrixXd tan_lat, Eigen::MatrixXd n);
Eigen::MatrixXd CalculateElp3(Eigen::MatrixXd v, Eigen::MatrixXd d_long, Eigen::MatrixXd cos_lat, Eigen::MatrixXd tan_lat, Eigen::MatrixXd n);
Eigen::MatrixXd CalculateElp4(Eigen::MatrixXd v, Eigen::MatrixXd d_long, Eigen::MatrixXd cos_lat, Eigen::MatrixXd tan_lat, Eigen::MatrixXd n);
Eigen::MatrixXd CalculateNlp2(Eigen::MatrixXd v, Eigen::MatrixXd d_long, Eigen::MatrixXd cos_lat, Eigen::MatrixXd sin_lat, Eigen::MatrixXd tan_lat, Eigen::MatrixXd n);
Eigen::MatrixXd CalculateNlp3(Eigen::MatrixXd v, Eigen::MatrixXd d_long, Eigen::MatrixXd cos_lat, Eigen::MatrixXd sin_lat, Eigen::MatrixXd tan_lat, Eigen::MatrixXd n);
Eigen::MatrixXd CalculateNlp4(Eigen::MatrixXd v, Eigen::MatrixXd d_long, Eigen::MatrixXd cos_lat, Eigen::MatrixXd sin_lat, Eigen::MatrixXd tan_lat, Eigen::MatrixXd n);
Eigen::MatrixXd CalculateNlp5(Eigen::MatrixXd v, Eigen::MatrixXd d_long, Eigen::MatrixXd cos_lat, Eigen::MatrixXd sin_lat, Eigen::MatrixXd tan_lat, Eigen::MatrixXd n);
CoordinatesUTM LatLong2UTM(Eigen::MatrixXd LatitutePoints, Eigen::MatrixXd LongitutePoints);