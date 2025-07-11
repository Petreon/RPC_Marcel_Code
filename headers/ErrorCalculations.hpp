#ifndef ERROR_CALCULATIONS_HPP
#define ERROR_CALCULATIONS_HPP

#include "../includes/Eigen/Dense"
#include "../headers/mainWork.hpp"
#include "MatrixSubSetting.hpp"
#include "StandardDeviation.hpp"
#include "latlong2utm.hpp"
PlanimetricErrorReturn calculatePlanimetricError(CoordinatesUTM LAT_LONG_to_E_N_F, CoordinatesUTM Train_E_N_F_Intersec_x, Eigen::MatrixXd IndexTrain);
AltimetricErrorReturn calculateAltimetricError(Eigen::MatrixXd h, Eigen::MatrixXd Matrix_h_intersec, Eigen::MatrixXd IndexTrain);
void CalculateSampleError(Eigen::MatrixXd& errorMatrix, int iterator, double mean_erro_plan_before, double mean_Train_erro_plan_after, double std_Train_erro_plan_antes, double std_Train_erro_plan_depois);

#endif // ERROR_CALCULATIONS_HPP