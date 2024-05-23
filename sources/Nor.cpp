// Include libraries and functions
#include "../includes/Eigen/Dense"
#include "mmq.cpp"
#include <iostream>

/*
struct to acesses the offset and scale 
values for a property to be normalized 
*/

typedef struct norm_values{
    long scale;
    long off;
} CorrectionValues;

// functions
/*
function to take the a general value related to each 
point (lat, long, height, line, collumn, for example) and normalize them
*/

long ElementNormalization(long value, long CorrectionFactor, long ScaleFactor){
    return ((value - CorrectionFactor) / ScaleFactor);
}

/*
Function to normalize each element of the matrix
The function takes an array that holds the offset and scale correction values for each property
like line, collumn, latitude, etc.
*/
Eigen::MatrixXd ImgNormalization(Eigen::MatrixXd img, CorrectionValues correction[]){
    int row = img.rows();
    int col = img.cols();

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            img(i,j) = ElementNormalization(img(i,j),correction[0].off,correction[0].scale);
        }
    }
    return img;
}
