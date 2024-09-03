#include <stdio.h>
#include <iostream> // IO C++ library
#include "../includes/Eigen/Dense"

double Polrfm(double rpc[20], double l, double b, double h);
/*
int main()
{
    // Declaração do vetor para armazenar os valores double
    double coeficientes[20];

    // Abre o arquivo para leitura
    FILE *arquivo;
    arquivo = fopen("coef_a1.txt", "r");

    // Verifica se o arquivo foi aberto com sucesso
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    // Lê os valores double do arquivo e armazena no vetor
    int i;
    for (i = 0; i < 20; i++)
    {
        fscanf(arquivo, "%lf", &coeficientes[i]);
    }

    // Fecha o arquivo
    fclose(arquivo);

    // Imprime os valores do vetor (opcional)
    for (i = 0; i < 20; i++)
    {
        printf("\n %lf ", coeficientes[i]);
    }

    printf("\n");

    double l = 0, b = 0, h = 0, resultado = 0;
    resultado = Polrfm(coeficientes, l, b, h);

    printf("O resultado do polinomio : %lf\n", resultado);

    return 0;
}
*/
double Polrfm_pedro(double rpc[20], double l, double b, double h)
{
    double somatorio;
    somatorio = rpc[0] + (rpc[1] * l) + (rpc[2] * b) + (rpc[3] * h) + (rpc[4] * l * b) + (rpc[5] * l * h) + (rpc[6] * b * h) + (rpc[7] * l * l) + (rpc[8] * b * b) + (rpc[9] * h * h) + (rpc[10] * b * l * h) + (rpc[11] * l * l * l) + (rpc[12] * l * b * b) + (rpc[13] * l * h * h) + (rpc[14] * l * l * b) + (rpc[15] * b * b * b) + (rpc[16] * b * h * h) + (rpc[17] * l * l * h) + (rpc[18] * b * b * h) + (rpc[19] * h * h * h);
    return somatorio;
};

Eigen::MatrixXd Polrfm(Eigen::MatrixXd B, Eigen::MatrixXd L, Eigen::MatrixXd H, Eigen::MatrixXd RPC)
{
    /*RPC matrix is a 20x1 matrix, this function should support every size of Vector with at least 1x1 size
    octave code:
     [ones(rows(B),1), L, B, H, L.*B, L.*H, B.*H, L.*L, B.*B, H.*H, B.*L.*H, L.*L.*L, L.*B.*B, L.*H.*H, L.*L.*B, B.*B.*B, B.*H.*H, L.*L.*H, B.*B.*H, H.*H.*H] * rpc;
     */

    int n = B.size();         // Number of rows
    Eigen::MatrixXd Z(n, 20); // Create the matrix with 20 columns as per the transformations

    // this is to support a multiple Z(x,20) matrix
    for (int i = 0; i < n; i++)
    {
        Z(i, 0) = (double)1;                      // Column of ones
        Z(i, 1) = L(i, 0);                        // L
        Z(i, 2) = B(i, 0);                        // B
        Z(i, 3) = H(i, 0);                        // H
        Z(i, 4) = L(i, 0) * B(i, 0);              // L .* B
        Z(i, 5) = L(i, 0) * H(i, 0);              // L .* H
        Z(i, 6) = B(i, 0) * H(i, 0);              // B .* H
        Z(i, 7) = L(i, 0) * L(i, 0);              // L .* L
        Z(i, 8) = B(i, 0) * B(i, 0);              // B .* B
        Z(i, 9) = H(i, 0) * H(i, 0);              // H .* H
        Z(i, 10) = (B(i, 0) * L(i, 0) * H(i, 0)); // B .* L .* H
        Z(i, 11) = L(i, 0) * L(i, 0) * L(i, 0);   // L .* L .* L
        Z(i, 12) = L(i, 0) * B(i, 0) * B(i, 0);   // L .* B .* B
        Z(i, 13) = L(i, 0) * H(i, 0) * H(i, 0);   // L .* H .* H
        Z(i, 14) = L(i, 0) * L(i, 0) * B(i, 0);   // L .* L .* B
        Z(i, 15) = B(i, 0) * B(i, 0) * B(i, 0);   // B .* B .* B
        Z(i, 16) = B(i, 0) * H(i, 0) * H(i, 0);   // B .* H .* H
        Z(i, 17) = L(i, 0) * L(i, 0) * H(i, 0);   // L .* L .* H
        Z(i, 18) = B(i, 0) * B(i, 0) * H(i, 0);   // B .* B .* H
        Z(i, 19) = H(i, 0) * H(i, 0) * H(i, 0);
    }

    Eigen::MatrixXd result = Z * RPC;

    return result;
}