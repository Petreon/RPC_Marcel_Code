#include "StandardDeviation.hpp"

double StandardDeviation(Eigen::MatrixXd matrix) {
    // Compute the mean
    double mean = matrix.mean();

    // Compute the variance
    double variance = (matrix.array() - mean).square().mean();

    // Compute the standard deviation
    double std_dev = std::sqrt(variance);
    
    return std_dev;
}