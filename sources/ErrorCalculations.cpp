#include "../headers/ErrorCalculations.hpp"
#include "../headers/utils/MatrixSubSetting.hpp"
#include "../headers/latlong2utm.hpp"

PlanimetricErrorReturn calculatePlanimetricError(CoordinatesUTM LAT_LONG_to_E_N_F, CoordinatesUTM Train_E_N_F_Intersec_x, Eigen::MatrixXd IndexTrain) {
    // Planimétrico
    PlanimetricErrorReturn calcs;
    //Train_erro_plan_antes = sqrt((LAT_E(IndexTrain, :) - Train_E_intersec_antes). ^ 2 + (LONG_N(IndexTrain, :) - Train_N_intersec_antes). ^ 2);
    Eigen::MatrixXd LAT_E   = MatrixSubSetting(LAT_LONG_to_E_N_F.East, IndexTrain);
    Eigen::MatrixXd LONG_N  = MatrixSubSetting(LAT_LONG_to_E_N_F.North, IndexTrain);
    
    Eigen::MatrixXd Train_erro_plan_antes = ( (LAT_E - Train_E_N_F_Intersec_x.East).array().pow(2) + (LONG_N - Train_E_N_F_Intersec_x.North).array().pow(2));
    Train_erro_plan_antes = Train_erro_plan_antes.array().sqrt();
   
    double Train_desv_erro_plan_antes = StandardDeviation(Train_erro_plan_antes);
    
    calcs.Error_planimetric = Train_erro_plan_antes;
    calcs.std_Error_plan    = Train_desv_erro_plan_antes;

    return calcs;
}


AltimetricErrorReturn calculateAltimetricError(Eigen::MatrixXd h, Eigen::MatrixXd Matrix_h_intersec, Eigen::MatrixXd IndexTrain) {
    // Planimétrico
    AltimetricErrorReturn calcs;

    //Test_erro_alt_antes = abs(h(IndexTest, :) - Test_h_intersec_antes);
    Eigen::MatrixXd new_h = MatrixSubSetting(h, IndexTrain);

    Eigen::MatrixXd Test_erro_alt_antes = (new_h - Matrix_h_intersec).array().abs();
    double desv_erro_alt    = StandardDeviation(Test_erro_alt_antes);

    calcs.Error_Altimetric  = Test_erro_alt_antes;
    calcs.std_Error_alti    = desv_erro_alt;

    return calcs;
}

void CalculateSampleError(Eigen::MatrixXd& errorMatrix, int iterator, double mean_erro_plan_before, double mean_Train_erro_plan_after, double std_Train_erro_plan_antes, double std_Train_erro_plan_depois) {

    errorMatrix(iterator, 0) = mean_erro_plan_before;
    errorMatrix(iterator, 1) = mean_Train_erro_plan_after;
    errorMatrix(iterator, 2) = std_Train_erro_plan_antes;
    errorMatrix(iterator, 3) = std_Train_erro_plan_depois;

}