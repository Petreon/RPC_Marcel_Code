// Include libraries and functions
#include "../includes/Eigen/Dense"
#include "structs.h"
#include "mmq.cpp"
#include <iostream>

// functions

AffineReturn Affine(Eigen::MatrixXd Line, Eigen::MatrixXd Sample, Eigen::MatrixXd LineMeas, Eigen::MatrixXd SampleMeas)
{
    /*
    This function enter 4 matrices and return 2 matrices

    The size of Matrix is defined from the Test points that you enter in the main function
    all the matrixes are 4x1, so the rows are dynamic but the columns always 1
    Nx1 matrices
    */
    AffineReturn Xa_V_Matrixes;
    int rows_size = Line.rows(); // Nx1 matrix

    // std::cout << Line << std::endl;
    // std::cout << Sample << std::endl;

    Eigen::MatrixXd A_matrix(rows_size, 6);
    // creating a matrix 4x6 111, line, sample e zeros
    A_matrix << Eigen::MatrixXd::Ones(rows_size, 1),
        Line,
        Sample,
        Eigen::MatrixXd::Zero(rows_size, 1),
        Eigen::MatrixXd::Zero(rows_size, 1),
        Eigen::MatrixXd::Zero(rows_size, 1);

    int num_rows = A_matrix.rows();

    // creating a new 4x6 matrix to append in the A matrix
    Eigen::MatrixXd new_rows(rows_size, 6);

    new_rows << Eigen::MatrixXd::Zero(rows_size, 1),
        Eigen::MatrixXd::Zero(rows_size, 1),
        Eigen::MatrixXd::Zero(rows_size, 1),
        Eigen::MatrixXd::Ones(rows_size, 1),
        Line,
        Sample;

    // Resize A to accommodate the new rows
    A_matrix.conservativeResize(A_matrix.rows() + rows_size, 6);

    // Append the new rows to A
    A_matrix.block(num_rows, 0, rows_size, 6) = new_rows;

    // std::cout << A_matrix << std::endl;

    // Constructing a L Matrix for itx a 2Nx1 matrix

    Eigen::MatrixXd L_matrix(2 * rows_size, 1);
    // subtracting the matrixes
    Eigen::MatrixXd line_LineMeas = Line - LineMeas;
    Eigen::MatrixXd Sample_SampleMeas = Sample - SampleMeas;
    // std::cout << line_LineMeas << std::endl;

    // substituing the values in L Matrix
    L_matrix.block(0, 0, line_LineMeas.rows(), 1) = line_LineMeas;
    L_matrix.block(4, 0, line_LineMeas.rows(), 1) = Sample_SampleMeas;
    // std::cout << L << std::endl;

    // what is mmq operation
    mmqReturn mmqOperation = mmq(A_matrix, L_matrix);

    // Xa need to be 6x1 and V 8x1
    Xa_V_Matrixes.Xa = mmqOperation.Xa;
    Xa_V_Matrixes.V = mmqOperation.V;

    return Xa_V_Matrixes;
};
