
#include <iostream>
#include "../includes/Eigen/Dense"
#include "../headers/ErrorCalculations.hpp"
#include "../headers/latlong2utm.hpp"

int main() {
    CoordinatesUTM lat_long_to_e_n_f;
    lat_long_to_e_n_f.East.resize(1, 1);
    lat_long_to_e_n_f.East(0, 0) = 1.0;
    lat_long_to_e_n_f.North.resize(1, 1);
    lat_long_to_e_n_f.North(0, 0) = 1.0;

    CoordinatesUTM train_e_n_f_intersec_x;
    train_e_n_f_intersec_x.East.resize(1, 1);
    train_e_n_f_intersec_x.East(0, 0) = 1.0;
    train_e_n_f_intersec_x.North.resize(1, 1);
    train_e_n_f_intersec_x.North(0, 0) = 1.0;

    Eigen::MatrixXd index_train(1, 1);
    index_train(0, 0) = 0;

    PlanimetricErrorReturn planimetric_error = calculatePlanimetricError(lat_long_to_e_n_f, train_e_n_f_intersec_x, index_train);

    Eigen::MatrixXd h(1, 1);
    h(0, 0) = 1.0;

    Eigen::MatrixXd matrix_h_intersec(1, 1);
    matrix_h_intersec(0, 0) = 1.0;

    AltimetricErrorReturn altimetric_error = calculateAltimetricError(h, matrix_h_intersec, index_train);

    Eigen::MatrixXd error_matrix(1, 4);

    CalculateSampleError(error_matrix, 0, 1.0, 1.0, 1.0, 1.0);

    std::cout << "Planimetric Error: " << planimetric_error.Error_planimetric << std::endl;
    std::cout << "Planimetric Std Error: " << planimetric_error.std_Error_plan << std::endl;
    std::cout << "Altimetric Error: " << altimetric_error.Error_Altimetric << std::endl;
    std::cout << "Altimetric Std Error: " << altimetric_error.std_Error_alti << std::endl;
    std::cout << "Error Matrix: " << error_matrix << std::endl;

    return 0;
}
