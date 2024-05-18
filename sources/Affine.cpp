// Include libraries and functions
#include "../includes/Eigen/Dense"
#include <iostream>

// functions

typedef struct AffineReturn
{
    Eigen::MatrixXd Xa;
    Eigen::MatrixXd V;
} AffineReturn;

AffineReturn Affine(Eigen::MatrixXd Line, Eigen::MatrixXd Sample, Eigen::MatrixXd LineMeas, Eigen::MatrixXd SampleMeas)
{
    /*
    This function enter 4 matrix and return 2 matrix
    The size of Matrix is defined from the Test points that you enter in the main function
    all the matrixes are 4x1, so the lines are dynamic but the row always 1
    */
    AffineReturn Xa_V_Matrixes;

    Eigen::MatrixXd A_matrix(Line.rows(), 6);
    // std::cout << Line << std::endl;
    // std::cout << Sample << std::endl;

    A_matrix << Eigen::MatrixXd::Ones(Line.rows(), 1),
        Line,
        Sample,
        Eigen::MatrixXd::Zero(Line.rows(), 1),
        Eigen::MatrixXd::Zero(Line.rows(), 1),
        Eigen::MatrixXd::Zero(Line.rows(), 1);

    int num_rows = A_matrix.rows();

    Eigen::MatrixXd new_rows(Line.rows(), 6);
    new_rows << Eigen::MatrixXd::Zero(Line.rows(), 1),
        Eigen::MatrixXd::Zero(Line.rows(), 1),
        Eigen::MatrixXd::Zero(Line.rows(), 1),
        Eigen::MatrixXd::Ones(Line.rows(), 1),
        Line,
        Sample;

    // Resize A to accommodate the new rows
    A_matrix.conservativeResize(A_matrix.rows() + Line.rows(), 6);

    // Append the new rows to A
    A_matrix.block(num_rows, 0, Line.rows(), 6) = new_rows;

    std::cout << A_matrix << std::endl;

    return Xa_V_Matrixes;
};
