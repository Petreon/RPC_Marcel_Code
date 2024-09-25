#pragma once

#include <iostream>
#include <vector>
#include <algorithm> // for std::shuffle
#include <random>    // for std::random_device and std::mt19937
#include "../../includes/Eigen/Dense"

Eigen::MatrixXd RandPermutation(int size);