#include "../../headers/utils/RandPerm.h"

Eigen::MatrixXd RandPermutation(int size) {
    // Create a vector with numbers from 0 to size-1
    Eigen::MatrixXd vec(1,size);
    for (int i = 0; i < size; ++i) {
        vec(0,i) = i;
    }

    // Seed for random number generator
    //std::random_device rd;
    //std::mt19937 g(rd());

    // Shuffle the vector
    //std::shuffle(vec.begin(), vec.end(), g);
    vec.Random();

    return vec;
}