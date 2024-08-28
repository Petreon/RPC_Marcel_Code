// Include libraries and functions
#include "../includes/Eigen/Dense"
#include <iostream>


// functions
double Deriv_H(double B, double L, double H, Eigen::MatrixXd rpcNumerator, Eigen::MatrixXd rpcDenominator) {
/* Reason to why used rpc_matrix.row(x).value() instead index[] is because Eigen can do more runtime errorproof in memory
    instead of accessing an wrong memory value, and with value() we already get the double value in matrix directly
    without pointers and convertions
    */

    /*
    Derivate for H value in relation of the Rpc's the calculus is based in this octave line:
    x = (3*rpc_num(20)*H^2 + 2*rpc_num(14)*H*L + 2*rpc_num(17)*H*B + 2*rpc_num(10)*H + rpc_num(18)*L^2 + rpc_num(11)*L*B + rpc_num(6)*L + rpc_num(19)*B^2 + rpc_num(7)*B + rpc_num(4))  
     /  
        (rpc_den(20)*H^3 + rpc_den(14)*H^2*L + rpc_den(17)*H^2*B + rpc_den(10)*H^2 + rpc_den(18)*H*L^2 + rpc_den(11)*H*L*B + rpc_den(6)*H*L + rpc_den(19)*H*B^2 + rpc_den(7)*H*B + rpc_den(4)*H + rpc_den(12)*L^3 + rpc_den(15)*L^2*B + rpc_den(8)*L^2 + rpc_den(13)*L*B^2 + rpc_den(5)*L*B + rpc_den(2)*L + rpc_den(16)*B^3 + rpc_den(9)*B^2 + rpc_den(3)*B + rpc_den(1))    
     -    
        (3*rpc_den(20)*H^2 + 2*rpc_den(14)*H*L + 2*rpc_den(17)*H*B + 2*rpc_den(10)*H + rpc_den(18)*L^2 + rpc_den(11)*L*B + rpc_den(6)*L + rpc_den(19)*B^2 + rpc_den(7)*B + rpc_den(4))
     *    
        (rpc_num(20)*H^3 + rpc_num(14)*H^2*L + rpc_num(17)*H^2*B + rpc_num(10)*H^2 + rpc_num(18)*H*L^2 + rpc_num(11)*H*L*B + rpc_num(6)*H*L + rpc_num(19)*H*B^2 + rpc_num(7)*H*B + rpc_num(4)*H + rpc_num(12)*L^3 + rpc_num(15)*L^2*B + rpc_num(8)*L^2 + rpc_num(13)*L*B^2 + rpc_num(5)*L*B + rpc_num(2)*L + rpc_num(16)*B^3 + rpc_num(9)*B^2 + rpc_num(3)*B + rpc_num(1) )    
     /      
        (rpc_den(20)*H^3 + rpc_den(14)*H^2*L + rpc_den(17)*H^2*B + rpc_den(10)*H^2 + rpc_den(18)*H*L^2 + rpc_den(11)*H*L*B + rpc_den(6)*H*L + rpc_den(19)*H*B^2 + rpc_den(7)*H*B + rpc_den(4)*H + rpc_den(12)*L^3 + rpc_den(15)*L^2*B + rpc_den(8)*L^2 + rpc_den(13)*L*B^2 + rpc_den(5)*L*B + rpc_den(2)*L + rpc_den(16)*B^3 + rpc_den(9)*B^2 + rpc_den(3)*B + rpc_den(1))^2;      
    */

   // doing this operation by parts, every part should return a double value:
    // 1° part:
    //  (3*rpc_num(20)*H^2 + 2*rpc_num(14)*H*L + 2*rpc_num(17)*H*B + 2*rpc_num(10)*H + rpc_num(18)*L^2 + rpc_num(11)*L*B + rpc_num(6)*L + rpc_num(19)*B^2 + rpc_num(7)*B + rpc_num(4))  

    double part1 = ((double)3*rpcNumerator.row(19).value() * std::pow(H,2) + (double)2*rpcNumerator.row(13).value() * H * L + (double)2*rpcNumerator.row(16).value() * H * B + (double)2*rpcNumerator.row(9).value() * H + rpcNumerator.row(17).value() * std::pow(L,2) + rpcNumerator.row(10).value() * L * B + rpcNumerator.row(5).value() * L + rpcNumerator.row(18).value() * std::pow(B,2) + rpcNumerator.row(6).value() * B + rpcNumerator.row(3).value());

    // 2° part:
    /*
     (rpc_den(20)*H^3 + rpc_den(14)*H^2*L + rpc_den(17)*H^2*B + rpc_den(10)*H^2 + rpc_den(18)*H*L^2 + rpc_den(11)*H*L*B + rpc_den(6)*H*L + rpc_den(19)*H*B^2 + rpc_den(7)*H*B + rpc_den(4)*H + rpc_den(12)*L^3 + rpc_den(15)*L^2*B + rpc_den(8)*L^2 + rpc_den(13)*L*B^2 + rpc_den(5)*L*B + rpc_den(2)*L + rpc_den(16)*B^3 + rpc_den(9)*B^2 + rpc_den(3)*B + rpc_den(1))    
    */

    double part2 = (rpcDenominator.row(19).value() * std::pow(H,3) + rpcDenominator.row(13).value() * std::pow(H,2) * L + rpcDenominator.row(16).value() * std::pow(H,2) * B + rpcDenominator.row(9).value() * std::pow(H,2) + rpcDenominator.row(17).value() * H * std::pow(L,2) + rpcDenominator.row(10).value() * H * L * B + rpcDenominator.row(5).value() * H * L + rpcDenominator.row(18).value() * H * std::pow(B,2) + rpcDenominator.row(6).value()* H * B + rpcDenominator.row(3).value() * H + rpcDenominator.row(11).value() * std::pow(L,3) + rpcDenominator.row(14).value() * std::pow(L,2) * B + rpcDenominator.row(7).value() * std::pow(L,2) + rpcDenominator.row(12).value() * L * std::pow(B,2) + rpcDenominator.row(4).value() * L * B + rpcDenominator.row(1).value() * L + rpcDenominator.row(15).value() * std::pow(B,3) + rpcDenominator.row(8).value() * std::pow(B,2) + rpcDenominator.row(2).value() * B + rpcDenominator.row(0).value());

    double part3 = ((double)3*rpcDenominator.row(19).value() * std::pow(H,2) + (double)2*rpcDenominator.row(13).value() * H * L + (double)2*rpcDenominator.row(16).value() * H * B + (double)2*rpcDenominator.row(9).value() * H + rpcDenominator.row(17).value() * std::pow(L,2) + rpcDenominator.row(10).value() * L * B + rpcDenominator.row(5).value() * L + rpcDenominator.row(18).value() * std::pow(B,2) + rpcDenominator.row(6).value() * B + rpcDenominator.row(3).value());


    double part4 = (rpcNumerator.row(19).value() * std::pow(H,3) + rpcNumerator.row(13).value() * std::pow(H,2) * L + rpcNumerator.row(16).value() * std::pow(H,2) * B + rpcNumerator.row(9).value() * std::pow(H,2) + rpcNumerator.row(17).value() * H * std::pow(L,2) + rpcNumerator.row(10).value() * H * L * B + rpcNumerator.row(5).value() * H * L + rpcNumerator.row(18).value() * H * std::pow(B,2) + rpcNumerator.row(6).value()* H * B + rpcNumerator.row(3).value() * H + rpcNumerator.row(11).value() * std::pow(L,3) + rpcNumerator.row(14).value() * std::pow(L,2) * B + rpcNumerator.row(7).value() * std::pow(L,2) + rpcNumerator.row(12).value() * L * std::pow(B,2) + rpcNumerator.row(4).value() * L * B + rpcNumerator.row(1).value() * L + rpcNumerator.row(15).value() * std::pow(B,3) + rpcNumerator.row(8).value() * std::pow(B,2) + rpcNumerator.row(2).value() * B + rpcNumerator.row(0).value());


    double part5 =(rpcDenominator.row(19).value() * std::pow(H,3) + rpcDenominator.row(13).value() * std::pow(H,2) * L + rpcDenominator.row(16).value() * std::pow(H,2) * B + rpcDenominator.row(9).value() * std::pow(H,2) + rpcDenominator.row(17).value() * H * std::pow(L,2) + rpcDenominator.row(10).value() * H * L * B + rpcDenominator.row(5).value() * H * L + rpcDenominator.row(18).value() * H * std::pow(B,2) + rpcDenominator.row(6).value()* H * B + rpcDenominator.row(3).value() * H + rpcDenominator.row(11).value() * std::pow(L,3) + rpcDenominator.row(14).value() * std::pow(L,2) * B + rpcDenominator.row(7).value() * std::pow(L,2) + rpcDenominator.row(12).value() * L * std::pow(B,2) + rpcDenominator.row(4).value() * L * B + rpcDenominator.row(1).value() * L + rpcDenominator.row(15).value() * std::pow(B,3) + rpcDenominator.row(8).value() * std::pow(B,2) + rpcDenominator.row(2).value() * B + rpcDenominator.row(0).value());

    part5 = std::pow(part5, 2);

    double result = part1 / part2 - part3 * part4 / part5;

    return result;
};
