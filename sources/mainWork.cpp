#include "Affine.hpp"
#include "Desnor.hpp"
#include "img2terrain.hpp"
#include "latlong2utm.hpp"
#include "utils/RandPerm.hpp"
#include "utils/MatrixSubSetting.hpp"
#include "RecalcRPC.hpp"

#include <stdio.h>
#include <stdlib.h>

#define NUM_ARQUIVOS 4
#define LINHAS_POR_ARQUIVO 20

#define NUM_ARQUIVOS2 3
#define LINHAS_POR_ARQUIVO2 36

#define NUM_ARQUIVOS3 2
#define LINHAS_POR_ARQUIVO3 36

int main() {
//1 ARQUIVOS DE ENTRADA DO PROGRAMA

//1.1 RPCs - Coeficientes da função - Presente nos arquivos .RPB de metadados da imagem

    float **coef1;
    float **coef2;
    FILE *fp;

//1.1.1 - RPCs da imagem 1 (matrizes colunas)
    // Alocação dinâmica da matriz
    coef1 = (float**)malloc(NUM_ARQUIVOS * sizeof(int*));
    for (int i = 0; i < NUM_ARQUIVOS; i++) {
        coef1[i] = (float*)malloc(LINHAS_POR_ARQUIVO * sizeof(float));
    }

    // Nomes dos arquivos (ajuste conforme necessário)
    char *nomes_arquivos[NUM_ARQUIVOS] = {"coef_a1.txt", "coef_b1.txt", "coef_c1.txt", "coef_d1.txt"};

    // Leitura dos arquivos e preenchimento da matriz
    for (int i = 0; i < NUM_ARQUIVOS; i++) {
        fp = fopen(nomes_arquivos[i], "r");
        if (fp == NULL) {
            printf("Erro ao abrir o arquivo: %s\n", nomes_arquivos[i]);
            exit(1);
        }

        for (int j = 0; j < LINHAS_POR_ARQUIVO; j++) {
            if (fscanf(fp, "%f", &coef1[i][j]) != 1) {
                printf("Erro ao ler o arquivo: %s\n", nomes_arquivos[i]);
                fclose(fp);
                exit(1);
            }
        }
//1.1.2 - RPCs da imagem 2 (matrizes colunas)
    // Alocação dinâmica da matriz 2
    coef2 = (float**)malloc(NUM_ARQUIVOS * sizeof(float*));
    for (int i = 0; i < NUM_ARQUIVOS; i++) {
        coef2[i] = (float*)malloc(LINHAS_POR_ARQUIVO * sizeof(float));
    }

    // Nomes dos arquivos (ajuste conforme necessário)
    char *nomes_arquivos2[NUM_ARQUIVOS] = {"coef_a2.txt", "coef_b2.txt", "coef_c2.txt", "coef_d2.txt"};

    // Leitura dos arquivos e preenchimento da matriz 2
    for (int i = 0; i < NUM_ARQUIVOS; i++) {
        fp = fopen(nomes_arquivos2[i], "r");
        if (fp == NULL) {
            printf("Erro ao abrir o arquivo: %s\n", nomes_arquivos2[i]);
            exit(1);
        }

        for (int j = 0; j < LINHAS_POR_ARQUIVO; j++) {
            if (fscanf(fp, "%f", &coef2[i][j]) != 1) {
                printf("Erro ao ler o arquivo: %s\n", nomes_arquivos2[i]);
                fclose(fp);
                exit(1);
            }
        }

//1.2 Coordenadas dos pontos de campo no espaço objeto (latitude, longitude e altitude geodésicas) - Pontos E-Foto + Pontos utilizados no projeto da Adriana
        float **coord;

    // Alocação dinâmica da matriz coord
    coord = (float**)malloc(NUM_ARQUIVOS2 * sizeof(float*));
    for (int i = 0; i < NUM_ARQUIVOS2; i++) {
        coord[i] = (float*)malloc(LINHAS_POR_ARQUIVO2 * sizeof(float));
    }

    // Nomes dos arquivos (ajuste conforme necessário)
    char *nomes_arquivos3[NUM_ARQUIVOS2] = {"lat_pc.txt", "long_pc.txt", "alt_pc.txt"};

    // Leitura dos arquivos e preenchimento da matriz coord
    for (int i = 0; i < NUM_ARQUIVOS2; i++) {
        fp = fopen(nomes_arquivos3[i], "r");
        if (fp == NULL) {
            printf("Erro ao abrir o arquivo: %s\n", nomes_arquivos3[i]);
            exit(1);
        }

        for (int j = 0; j < LINHAS_POR_ARQUIVO2; j++) {
            if (fscanf(fp, "%f", &coord[i][j]) != 1) {
                printf("Erro ao ler o arquivo: %s\n", nomes_arquivos3[i]);
                fclose(fp);
                exit(1);
            }
        }

//1.3 Coordenadas dos pontos de campo no espaço imagem (medidos/observados na imagem) - " + "
        int **coord2;
        int **coord3;
        


    //1.3.1 - Para a imagem 1

    // Alocação dinâmica da matriz coord2
    coord2 = (int**)malloc(NUM_ARQUIVOS3 * sizeof(int*));
    for (int i = 0; i < NUM_ARQUIVOS3; i++) {
        coord2[i] = (int*)malloc(LINHAS_POR_ARQUIVO3 * sizeof(int));
    }

    // Nomes dos arquivos (ajuste conforme necessário)
    char *nomes_arquivos4[NUM_ARQUIVOS3] = {"l1_pc.txt", "c1_pc.txt"};

    // Leitura dos arquivos e preenchimento da matriz coord2
    for (int i = 0; i < NUM_ARQUIVOS3; i++) {
        fp = fopen(nomes_arquivos4[i], "r");
        if (fp == NULL) {
            printf("Erro ao abrir o arquivo: %s\n", nomes_arquivos4[i]);
            exit(1);
        }

        for (int j = 0; j < LINHAS_POR_ARQUIVO3; j++) {
            if (fscanf(fp, "%d", &coord2[i][j]) != 1) {
                printf("Erro ao ler o arquivo: %s\n", nomes_arquivos4[i]);
                fclose(fp);
                exit(1);
            }
        }

    //1.3.2 - Para a imagem 2

    // Alocação dinâmica da matriz coord3
    coord3 = (int**)malloc(NUM_ARQUIVOS3 * sizeof(int*));
    for (int i = 0; i < NUM_ARQUIVOS3; i++) {
        coord3[i] = (int*)malloc(LINHAS_POR_ARQUIVO3 * sizeof(int));
    }

     // Nomes dos arquivos (ajuste conforme necessário)
    char *nomes_arquivos5[NUM_ARQUIVOS3] = {"l2_pc.txt", "c2_pc.txt"};

    // Leitura dos arquivos e preenchimento da matriz coord3
    for (int i = 0; i < NUM_ARQUIVOS3; i++) {
        fp = fopen(nomes_arquivos5[i], "r");
        if (fp == NULL) {
            printf("Erro ao abrir o arquivo: %s\n", nomes_arquivos5[i]);
            exit(1);
        }

        for (int j = 0; j < LINHAS_POR_ARQUIVO3; j++) {
            if (fscanf(fp, "%d", &coord3[i][j]) != 1) {
                printf("Erro ao ler o arquivo: %s\n", nomes_arquivos5[i]);
                fclose(fp);
                exit(1);
            }
        }

//2 PARÂMETROS DA IMAGEM (OFFSET E SCALE) - Presente nos arquivos .RPB de metadados da imagem

        fclose(fp);
    }

    // Imprimindo a matriz (opcional)
    for (int i = 0; i < NUM_ARQUIVOS; i++) {
        for (int j = 0; j < LINHAS_POR_ARQUIVO; j++) {
            printf("%d ", coef1[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < NUM_ARQUIVOS; i++) {
        for (int j = 0; j < LINHAS_POR_ARQUIVO; j++) {
            printf("%d ", coef2[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < NUM_ARQUIVOS2; i++) {
        for (int j = 0; j < LINHAS_POR_ARQUIVO2; j++) {
            printf("%d ", coord[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < NUM_ARQUIVOS3; i++) {
        for (int j = 0; j < LINHAS_POR_ARQUIVO3; j++) {
            printf("%d ", coord2[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < NUM_ARQUIVOS3; i++) {
        for (int j = 0; j < LINHAS_POR_ARQUIVO3; j++) {
            printf("%d ", coord3[i][j]);
        }
        printf("\n");
    }

    // Liberando a memória alocada
    for (int i = 0; i < NUM_ARQUIVOS; i++) {
        free(coef1[i]);
    }
    free(coef1);
    for (int i = 0; i < NUM_ARQUIVOS; i++) {
        free(coef2[i]);
    }
    free(coef2);
    for (int i = 0; i < NUM_ARQUIVOS2; i++) {
        free(coord[i]);
    }
    free(coord);
    for (int i = 0; i < NUM_ARQUIVOS3; i++) {
        free(coord2[i]);
    }
    free(coord2);
    for (int i = 0; i < NUM_ARQUIVOS3; i++) {
        free(coord3[i]);
    }
    free(coord3);

    return 0;
}


//2 PARÂMETROS DA IMAGEM (OFFSET E SCALE) - Presente nos arquivos .RPB de metadados da imagem

        fclose(fp);
    }

    // Imprimindo a matriz (opcional)
    for (int i = 0; i < NUM_ARQUIVOS; i++) {
        for (int j = 0; j < LINHAS_POR_ARQUIVO; j++) {
            printf("%d ", coef1[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < NUM_ARQUIVOS; i++) {
        for (int j = 0; j < LINHAS_POR_ARQUIVO; j++) {
            printf("%d ", coef2[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < NUM_ARQUIVOS2; i++) {
        for (int j = 0; j < LINHAS_POR_ARQUIVO2; j++) {
            printf("%d ", coord[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < NUM_ARQUIVOS3; i++) {
        for (int j = 0; j < LINHAS_POR_ARQUIVO3; j++) {
            printf("%d ", coord2[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < NUM_ARQUIVOS3; i++) {
        for (int j = 0; j < LINHAS_POR_ARQUIVO3; j++) {
            printf("%d ", coord3[i][j]);
        }
        printf("\n");
    }

    // Liberando a memória alocada
    for (int i = 0; i < NUM_ARQUIVOS; i++) {
        free(coef1[i]);
    }
    free(coef1);
    for (int i = 0; i < NUM_ARQUIVOS; i++) {
        free(coef2[i]);
    }
    free(coef2);
    for (int i = 0; i < NUM_ARQUIVOS2; i++) {
        free(coord[i]);
    }
    free(coord);
    for (int i = 0; i < NUM_ARQUIVOS3; i++) {
        free(coord2[i]);
    }
    free(coord2);
    for (int i = 0; i < NUM_ARQUIVOS3; i++) {
        free(coord3[i]);
    }
    free(coord3);

    return 0;
}


//2 PARÂMETROS DA IMAGEM (OFFSET E SCALE) - Presente nos arquivos .RPB de metadados da imagem
// TODO: GET THIS FROM FILE METADATA
//2.2.1 Parâmetros de "Offset" e "scale" da imagem 1
#define LINE_OFF1       16225
#define LINE_SCALE1     16506
#define SAMPLE_OFF1     17577  
#define SAMPLE_SCALE1   17808
#define LAT_OFF1        -22.9529  
#define LAT_SCALE1      0.0806
#define LONG_OFF1       -43.1942
#define LONG_SCALE1     0.0873
#define HEIGHT_OFF1     307
#define HEIGHT_SCALE1   500

//2.2.2 Parâmetros de "Offset" e "scale" da imagem 2
#define LINE_OFF2       17282
#define LINE_SCALE2     17419
#define SAMPLE_OFF2     16531 
#define SAMPLE_SCALE2   16571
#define LAT_OFF2        -22.9517  
#define LAT_SCALE2      0.0794
#define LONG_OFF2       -43.1703 
#define LONG_SCALE2     0.0816
#define HEIGHT_OFF2     225   
#define HEIGHT_SCALE2   500;

//For the 1° image
Eigen::MatrixXd a1(20, 1);
Eigen::MatrixXd b1(20, 1);
Eigen::MatrixXd c1(20, 1);
Eigen::MatrixXd d1(20, 1);
//for the 2° image
Eigen::MatrixXd a2(20, 1);
Eigen::MatrixXd b2(20, 1);
Eigen::MatrixXd c2(20, 1);
Eigen::MatrixXd d2(20, 1);





int runTimes = 10;

int main(int argc, char* argv[]){
    /*
    argc the number of command lines,
    argv the command lines itself, //TODO: implent this for the future
    check if its okay
    command line: <train_points> <runTimes>
    */

    int trainPoints = 4;
    int AvailablePoints = 18; // TODO: take this after reading the file and get how many points have for the application

    //Control Points in Coordinates
    Eigen::MatrixXd B1_pc(AvailablePoints, 1); //This is variable depending on how many point disponible you have
    Eigen::MatrixXd L1_pc(AvailablePoints, 1);
    Eigen::MatrixXd H1_pc(AvailablePoints,1);

    Eigen::MatrixXd B2_pc(AvailablePoints, 1);
    Eigen::MatrixXd L2_pc(AvailablePoints, 1);
    Eigen::MatrixXd H2_pc(AvailablePoints, 1);

    //Control Points in Pixel
    Eigen::MatrixXd Line1(AvailablePoints, 1);
    Eigen::MatrixXd Sample1(AvailablePoints, 1); // in reality this is Colmun pixel of the control point in the image

    Eigen::MatrixXd Line2(AvailablePoints, 1);
    Eigen::MatrixXd Sample2(AvailablePoints, 1); // in reality this is Colmun pixel of the control point in the image //TODO: Change to column


    for (int i = 0; i < runTimes; i++){

        //1° Point Sorting to train
        //this logic can be changed but this works for now, im following this way because is the way that was used in octave code
        Eigen::MatrixXd SORTITION   = RandPermutation(B1_pc.rows());// SORTITION creates a vector of x elements with numbers from 0 to x in a random order
        Eigen::MatrixXd IndexTrain  = SORTITION.block(0, 0, 1, trainPoints);
        Eigen::MatrixXd IndexTest   = SORTITION.block(0, trainPoints, 1, B1_pc.rows()); //get the rest of the elements that is not in indextrain
        

        // 2° RPCs Recalculating / Adjustment // What is a1 and c1?
        //Obs MatrixSubSetting function is the same as this sintaxe in octave B1_pc(IndexTrain,:)
        //[new_a1, new_c1] = RecalcRPC(B1_pc(IndexTrain, :), L1_pc(IndexTrain, :), H1_pc(IndexTrain, :), a1, b1, c1, d1, Line1(IndexTrain, :), Sample1(IndexTrain, :), LINE_OFF1, LINE_SCALE1, SAMPLE_OFF1, SAMPLE_SCALE1);
        //[new_a2, new_c2] = RecalcRPC(B2_pc(IndexTrain, :), L2_pc(IndexTrain, :), H2_pc(IndexTrain, :), a2, b2, c2, d2, Line2(IndexTrain, :), Sample2(IndexTrain, :), LINE_OFF2, LINE_SCALE2, SAMPLE_OFF2, SAMPLE_SCALE2);
        RecalcReturn new_a1_c1 = RecalcRPC(MatrixSubSetting(B1_pc, IndexTrain), MatrixSubSetting(L1_pc, IndexTrain), MatrixSubSetting(H1_pc, IndexTrain), a1, b1, c1, d1, MatrixSubSetting(Line1, IndexTrain), MatrixSubSetting(Sample1, IndexTrain), LINE_OFF1, LINE_SCALE1, SAMPLE_OFF1, SAMPLE_SCALE1);
        RecalcReturn new_a2_c2 = RecalcRPC(MatrixSubSetting(B2_pc, IndexTrain), MatrixSubSetting(L2_pc, IndexTrain), MatrixSubSetting(H2_pc, IndexTrain), a2, b2, c2, d2, MatrixSubSetting(Line2, IndexTrain), MatrixSubSetting(Sample2, IndexTrain), LINE_OFF2, LINE_SCALE2, SAMPLE_OFF2, SAMPLE_SCALE2);


        // 5.3 Calculate the coordinates of terrain latitude, longitude and altitude

        // 5.3.1 - For the training points - before and after
        Coeficients Coef_Img1, Coef_Img2, Coef_Img1_new, Coef_Img2_new;
        Coef_Img1.a = a1; Coef_Img1.b = b1; Coef_Img1.c = c1; Coef_Img1.d = d1;
        Coef_Img2.a = a1; Coef_Img2.b = b1; Coef_Img2.c = c1; Coef_Img2.d = d1;

        Coef_Img1_new.a = new_a1_c1.Calc_rpc_nl; Coef_Img1_new.b = b1; Coef_Img1_new.c = new_a1_c1.Calc_rpc_ns; Coef_Img1_new.d = d1;
        Coef_Img2_new.a = a1; Coef_Img2_new.b = a1; Coef_Img2_new.c = a1; Coef_Img2_new.d = a1;
        

        // Antes
        //Coordinates Train_lat_long_h_before = SpacialInterssection(MatrixSubSetting(Line1, IndexTrain), MatrixSubSetting(Sample1, IndexTrain), MatrixSubSetting(Line2, IndexTrain), MatrixSubSetting(Sample2, IndexTrain), a1, b1, c1, d1, a2, b2, c2, d2, LINE_OFF1, SAMPLE_OFF1, LAT_OFF1, LONG_OFF1, HEIGHT_OFF1, LINE_SCALE1, SAMPLE_SCALE1, LAT_SCALE1, LONG_SCALE1, HEIGHT_SCALE1, LINE_OFF2, SAMPLE_OFF2, LAT_OFF2, LONG_OFF2, HEIGHT_OFF2, LINE_SCALE2, SAMPLE_SCALE2, LAT_SCALE2, LONG_SCALE2, HEIGHT_SCALE2);
        Coordinates Train_lat_long_h_before = SpacialInterssection();

        // Depois
        Coordinates Train_lat_long_h_after = SpacialInterssection(Line1,IndexTrain), Sample1,IndexTrain), Line2,IndexTrain), Sample2,IndexTrain), new_a1, b1, new_c1, d1, new_a2, b2, new_c2, d2, LINE_OFF1, SAMPLE_OFF1, LAT_OFF1, LONG_OFF1, HEIGHT_OFF1, LINE_SCALE1, SAMPLE_SCALE1, LAT_SCALE1, LONG_SCALE1, HEIGHT_SCALE1, LINE_OFF2, SAMPLE_OFF2, LAT_OFF2, LONG_OFF2, HEIGHT_OFF2, LINE_SCALE2, SAMPLE_SCALE2, LAT_SCALE2, LONG_SCALE2, HEIGHT_SCALE2);

        // 5.3.1 - Para os pontos de teste - antes e depois

        // Antes
        Coordinates Tests_lat_long_h_before = SpacialInterssection(Line1,IndexTest), Sample1,IndexTest), Line2,IndexTest), Sample2,IndexTest), a1, b1, c1, d1, a2, b2, c2, d2, LINE_OFF1, SAMPLE_OFF1, LAT_OFF1, LONG_OFF1, HEIGHT_OFF1, LINE_SCALE1, SAMPLE_SCALE1, LAT_SCALE1, LONG_SCALE1, HEIGHT_SCALE1, LINE_OFF2, SAMPLE_OFF2, LAT_OFF2, LONG_OFF2, HEIGHT_OFF2, LINE_SCALE2, SAMPLE_SCALE2, LAT_SCALE2, LONG_SCALE2, HEIGHT_SCALE2);

        // Depois
        Coordinates Tests_lat_long_h_after = SpacialInterssection(Line1,IndexTest), Sample1,IndexTest), Line2,IndexTest), Sample2,IndexTest), new_a1, b1, new_c1, d1, new_a2, b2, new_c2, d2, LINE_OFF1, SAMPLE_OFF1, LAT_OFF1, LONG_OFF1, HEIGHT_OFF1, LINE_SCALE1, SAMPLE_SCALE1, LAT_SCALE1, LONG_SCALE1, HEIGHT_SCALE1, LINE_OFF2, SAMPLE_OFF2, LAT_OFF2, LONG_OFF2, HEIGHT_OFF2, LINE_SCALE2, SAMPLE_SCALE2, LAT_SCALE2, LONG_SCALE2, HEIGHT_SCALE2);

    }


    return 0;
}
