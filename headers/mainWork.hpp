#pragma once
#include "../includes/Eigen/Dense"

typedef struct PlanimetricErrorReturn {
    Eigen::MatrixXd Error_planimetric;
    double std_Error_plan;
} PlanimetricError ;

PlanimetricErrorReturn PlanimetricError(CoordinatesUTM LAT_LONG_to_E_N_F, CoordinatesUTM Train_E_N_F_Intersec_before, Eigen::MatrixXd IndexTrain);

typedef struct AltimetricErrorReturn {
    Eigen::MatrixXd Error_Altimetric;
    double std_Error_alti;
} AltimetricError;

AltimetricErrorReturn AltimetricError(CoordinatesUTM LAT_LONG_to_E_N_F, CoordinatesUTM Train_E_N_F_Intersec_before, Eigen::MatrixXd IndexTrain);

Eigen::MatrixXd CalculateSampleError(Eigen::MatrixXd errorMatrix, int iterator, double mean_erro_plan_before, double mean_Train_erro_plan_after, double std_Train_erro_plan_antes, double std_Train_erro_plan_depois);