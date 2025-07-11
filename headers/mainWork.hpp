#pragma once
#include "../includes/Eigen/Dense"

struct PlanimetricErrorReturn {
    Eigen::MatrixXd Error_planimetric;
    double std_Error_plan;
};

struct AltimetricErrorReturn {
    Eigen::MatrixXd Error_Altimetric;
    double std_Error_alti;
};

