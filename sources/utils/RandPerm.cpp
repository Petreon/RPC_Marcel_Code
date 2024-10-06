#include <vector>
#include "RandPerm.hpp"

Eigen::MatrixXd RandPermutation(int size) {
    // Create a vector with numbers from 0 to size-1
    std::vector<double> vec;
    Eigen::MatrixXd vecReturn(1,size);
    for (int i = 0; i < size; ++i) {
        vec.push_back(i);
    }

    // Seed for random number generator
    std::random_device rd;
    std::mt19937 g(rd());

    // Shuffle the vector
    std::shuffle(vec.begin(), vec.end(), g);
    
    //append in the matrix

    for (int i = 0; i < size; ++i) {
        vecReturn(0,i) = vec[i];
    }

    return vecReturn;
}