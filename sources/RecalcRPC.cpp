// Include libraries and functions
#include "../includes/Eigen/Dense"
#include <memory>
#include <iostream>
#include "Affine.hpp"
#include "Polrfm.hpp"
#include "structs.hpp"
#include "Desnor.hpp"
#include "Nor.hpp"

// functions
RecalcReturn RecalcRPC(Eigen::MatrixXd Bn, Eigen::MatrixXd Ln, Eigen::MatrixXd Hn, Eigen::MatrixXd rpc_nl, Eigen::MatrixXd rpc_dl, Eigen::MatrixXd rpc_ns, Eigen::MatrixXd rpc_ds, Eigen::MatrixXd LineMeas, Eigen::MatrixXd SampleMeas, double Line_Off, double Line_Scale, double Sample_Off, double Sample_Scale)
{

    RecalcReturn Rpcs_result;
    // the polimorf result can be result in a 1x1 matrix if needed

    Eigen::MatrixXd L = Polrfm(Bn, Ln, Hn, rpc_nl).array() / Polrfm(Bn, Ln, Hn, rpc_dl).array(); // OK CHECKED
    Eigen::MatrixXd S = Polrfm(Bn, Ln, Hn, rpc_ns).array() / Polrfm(Bn, Ln, Hn, rpc_ds).array(); // OK CHECKED

    CorrectionValues LineValues;
    LineValues.off = Line_Off;
    LineValues.scale = Line_Scale;

    CorrectionValues SampleValues;
    SampleValues.off = Sample_Off;
    SampleValues.scale = Sample_Scale;

    // Eigen::MatrixXd Line = ImgDesnormalization(L, &LineValues); Dont working
    // Eigen::MatrixXd Sample = ImgDesnormalization(S, &SampleValues);

    Eigen::MatrixXd Line = Desnor(L, Line_Off, Line_Scale);
    Eigen::MatrixXd Sample = Desnor(S, Sample_Off, Sample_Scale);

    AffineReturn AffineResult = Affine(Line, Sample, LineMeas, SampleMeas);

    double A0L = ElementNormalization(AffineResult.Xa(0, 0), 0, Line_Scale);

    Eigen::MatrixXd Calc_rpc_nl = rpc_nl - rpc_dl * A0L;

    double B0L = ElementNormalization(AffineResult.Xa(3, 0), 0, Sample_Scale);
    Eigen::MatrixXd Calc_rpc_ns = rpc_ns - rpc_ds * B0L;

    std::cout
        << "Result in RecalcRPC:" << std::endl;
    std::cout << Calc_rpc_nl << std::endl
              << std::endl;
    std::cout << Calc_rpc_ns << std::endl;

    Rpcs_result.Calc_rpc_nl = Calc_rpc_nl;
    Rpcs_result.Calc_rpc_ns = Calc_rpc_ns;

    return Rpcs_result;
};