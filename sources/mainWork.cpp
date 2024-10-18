#include "Affine.hpp"
#include "Desnor.hpp"
#include "img2terrain.hpp"
#include "latlong2utm.hpp"
#include "utils/RandPerm.hpp"
#include "utils/MatrixSubSetting.hpp"
#include "RecalcRPC.hpp"

#include <stdio.h>
#include <stdlib.h>



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

//RPCS For the 1° image
Eigen::MatrixXd a1(20, 1);
Eigen::MatrixXd b1(20, 1);
Eigen::MatrixXd c1(20, 1);
Eigen::MatrixXd d1(20, 1);
//RPCs for the 2° image
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
    Eigen::MatrixXd H1_pc(AvailablePoints, 1);

    Eigen::MatrixXd B2_pc(AvailablePoints, 1);
    Eigen::MatrixXd L2_pc(AvailablePoints, 1);
    Eigen::MatrixXd H2_pc(AvailablePoints, 1);

    //Control Points in Pixel
    Eigen::MatrixXd Line1(AvailablePoints, 1);
    Eigen::MatrixXd Sample1(AvailablePoints, 1); // in reality this is Colmun pixel of the controls point in the image, 

    Eigen::MatrixXd Line2(AvailablePoints, 1);
    Eigen::MatrixXd Sample2(AvailablePoints, 1); // in reality this is Colmun pixel of the controls point in the image //TODO: Change to column


    Coeficients Coef_Img1, Coef_Img2, Coef_Img1_new, Coef_Img2_new; //Structure used to SpacialInterssection function
    CorrectionValues l1Correction, s1Correction, l2Correction, s2Correction, latCorrection1, longCorrection1, hCorrection1, latCorrection2, longCorrection2, hCorrection2; //Structure used to SpacialInterssection function


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
        RecalcReturn new_a1_c1 = RecalcRPC(MatrixSubSetting(B1_pc, IndexTrain), MatrixSubSetting(L1_pc, IndexTrain), MatrixSubSetting(H1_pc, IndexTrain), a1, b1, c1, d1, MatrixSubSetting(Line1, IndexTrain), MatrixSubSetting(Sample1, IndexTrain), LINE_OFF1, LINE_SCALE1, SAMPLE_OFF1, SAMPLE_SCALE1); //TODO: this macros need to change to variables to make it dinamically in the future
        RecalcReturn new_a2_c2 = RecalcRPC(MatrixSubSetting(B2_pc, IndexTrain), MatrixSubSetting(L2_pc, IndexTrain), MatrixSubSetting(H2_pc, IndexTrain), a2, b2, c2, d2, MatrixSubSetting(Line2, IndexTrain), MatrixSubSetting(Sample2, IndexTrain), LINE_OFF2, LINE_SCALE2, SAMPLE_OFF2, SAMPLE_SCALE2);


        // 5.3 Calculate the coordinates of terrain latitude, longitude and altitude

        // 5.3.1 - For the training points - before and after
        Coef_Img1.a = a1; Coef_Img1.b = b1; Coef_Img1.c = c1; Coef_Img1.d = d1;
        Coef_Img2.a = a2; Coef_Img2.b = b2; Coef_Img2.c = c2; Coef_Img2.d = d2;

        Coef_Img1_new.a = new_a1_c1.Calc_rpc_nl; Coef_Img1_new.b = b1; Coef_Img1_new.c = new_a1_c1.Calc_rpc_ns; Coef_Img1_new.d = d1;
        Coef_Img2_new.a = new_a2_c2.Calc_rpc_nl; Coef_Img2_new.b = b2; Coef_Img2_new.c = new_a2_c2.Calc_rpc_ns; Coef_Img2_new.d = d2;
        
        //This part need to be variables instead macros, if they are constants and dont change in the code, it can be put outside the loop
        l1Correction.scale      = LINE_SCALE1    ; l1Correction.off      = LINE_OFF1; 
        s1Correction.scale      = SAMPLE_SCALE1  ; s1Correction.off      = SAMPLE_OFF1;
        
        latCorrection1.scale    = LAT_SCALE1     ; latCorrection1.off    = LAT_OFF1;
        longCorrection1.scale   = LONG_SCALE1    ; longCorrection1.off   = LONG_OFF1;
        hCorrection1.scale      = HEIGHT_SCALE1  ; hCorrection1.off      = HEIGHT_OFF1;
        
        //Structure for the second image
        l2Correction.scale      = LINE_SCALE2    ; l2Correction.off      = LINE_OFF2;
        s2Correction.scale      = SAMPLE_SCALE2  ; s2Correction.off      = SAMPLE_OFF2;

        latCorrection2.scale    = LAT_SCALE2     ; latCorrection2.off    = LAT_OFF2;
        longCorrection2.scale   = LONG_SCALE2    ; longCorrection2.off   = LONG_OFF2;
        hCorrection2.scale      = HEIGHT_SCALE2  ; hCorrection2.off      = HEIGHT_OFF2;

        // Before
        //Coordinates Train_lat_long_h_before = SpacialInterssection(MatrixSubSetting(Line1, IndexTrain), MatrixSubSetting(Sample1, IndexTrain), MatrixSubSetting(Line2, IndexTrain), MatrixSubSetting(Sample2, IndexTrain), a1, b1, c1, d1, a2, b2, c2, d2, LINE_OFF1, SAMPLE_OFF1, LAT_OFF1, LONG_OFF1, HEIGHT_OFF1, LINE_SCALE1, SAMPLE_SCALE1, LAT_SCALE1, LONG_SCALE1, HEIGHT_SCALE1, LINE_OFF2, SAMPLE_OFF2, LAT_OFF2, LONG_OFF2, HEIGHT_OFF2, LINE_SCALE2, SAMPLE_SCALE2, LAT_SCALE2, LONG_SCALE2, HEIGHT_SCALE2);
        Coordinates Train_lat_long_h_before = SpacialInterssection(Coef_Img1, Coef_Img2, MatrixSubSetting(Line1, IndexTrain) , MatrixSubSetting(Sample1, IndexTrain),MatrixSubSetting(Line2, IndexTrain) , MatrixSubSetting(Sample2, IndexTrain), l1Correction, s1Correction, l2Correction, s2Correction, latCorrection1, longCorrection1, hCorrection1, latCorrection2, longCorrection2, hCorrection2);

        // After
        //Coordinates Train_lat_long_h_after = SpacialInterssection(Line1,IndexTrain), Sample1,IndexTrain), Line2,IndexTrain), Sample2,IndexTrain), new_a1, b1, new_c1, d1, new_a2, b2, new_c2, d2, LINE_OFF1, SAMPLE_OFF1, LAT_OFF1, LONG_OFF1, HEIGHT_OFF1, LINE_SCALE1, SAMPLE_SCALE1, LAT_SCALE1, LONG_SCALE1, HEIGHT_SCALE1, LINE_OFF2, SAMPLE_OFF2, LAT_OFF2, LONG_OFF2, HEIGHT_OFF2, LINE_SCALE2, SAMPLE_SCALE2, LAT_SCALE2, LONG_SCALE2, HEIGHT_SCALE2);
        Coordinates Train_lat_long_h_after  = SpacialInterssection(Coef_Img1_new, Coef_Img2_new, MatrixSubSetting(Line1, IndexTrain) , MatrixSubSetting(Sample1, IndexTrain),MatrixSubSetting(Line2, IndexTrain) , MatrixSubSetting(Sample2, IndexTrain), l1Correction, s1Correction, l2Correction, s2Correction, latCorrection1, longCorrection1, hCorrection1, latCorrection2, longCorrection2, hCorrection2);

        // 5.3.1 - For the tests points - before and after

        // Before
        //Coordinates Tests_lat_long_h_before = SpacialInterssection(Line1,IndexTest), Sample1,IndexTest), Line2,IndexTest), Sample2,IndexTest), a1, b1, c1, d1, a2, b2, c2, d2, LINE_OFF1, SAMPLE_OFF1, LAT_OFF1, LONG_OFF1, HEIGHT_OFF1, LINE_SCALE1, SAMPLE_SCALE1, LAT_SCALE1, LONG_SCALE1, HEIGHT_SCALE1, LINE_OFF2, SAMPLE_OFF2, LAT_OFF2, LONG_OFF2, HEIGHT_OFF2, LINE_SCALE2, SAMPLE_SCALE2, LAT_SCALE2, LONG_SCALE2, HEIGHT_SCALE2);
        Coordinates Train_lat_long_h_before = SpacialInterssection(Coef_Img1, Coef_Img2, MatrixSubSetting(Line1, IndexTest) , MatrixSubSetting(Sample1, IndexTest),MatrixSubSetting(Line2, IndexTest) , MatrixSubSetting(Sample2, IndexTest), l1Correction, s1Correction, l2Correction, s2Correction, latCorrection1, longCorrection1, hCorrection1, latCorrection2, longCorrection2, hCorrection2);

        // After
        //Coordinates Tests_lat_long_h_after = SpacialInterssection(Line1,IndexTest), Sample1,IndexTest), Line2,IndexTest), Sample2,IndexTest), new_a1, b1, new_c1, d1, new_a2, b2, new_c2, d2, LINE_OFF1, SAMPLE_OFF1, LAT_OFF1, LONG_OFF1, HEIGHT_OFF1, LINE_SCALE1, SAMPLE_SCALE1, LAT_SCALE1, LONG_SCALE1, HEIGHT_SCALE1, LINE_OFF2, SAMPLE_OFF2, LAT_OFF2, LONG_OFF2, HEIGHT_OFF2, LINE_SCALE2, SAMPLE_SCALE2, LAT_SCALE2, LONG_SCALE2, HEIGHT_SCALE2);
        Coordinates Train_lat_long_h_after  = SpacialInterssection(Coef_Img1_new, Coef_Img2_new, MatrixSubSetting(Line1, IndexTest) , MatrixSubSetting(Sample1, IndexTest),MatrixSubSetting(Line2, IndexTest) , MatrixSubSetting(Sample2, IndexTest), l1Correction, s1Correction, l2Correction, s2Correction, latCorrection1, longCorrection1, hCorrection1, latCorrection2, longCorrection2, hCorrection2);

        //6 Conversion of this coordinates to UTM. i think is UTM 24 - E, go into the latlong2utm function to know the 
	
	    //6.1 For the training points 
	
        // [Train_E_intersec_antes, Train_N_intersec_antes, Train_Fuso_intersec_antes] = latlong2utm(Train_lat_intersec_antes, Train_long_intersec_antes);
        // [Train_E_intersec_depois, Train_N_intersec_depois, Train_Fuso_intersec_depois] = latlong2utm(Train_lat_intersec_depois, Train_long_intersec_depois);
        
        // % 6.2 Para os pontos de teste

        // [Test_E_intersec_antes, Test_N_intersec_antes, Test_Fuso_intersec_antes] = latlong2utm(Test_lat_intersec_antes, Test_long_intersec_antes);
        // [Test_E_intersec_depois, Test_N_intersec_depois, Test_Fuso_intersec_depois] = latlong2utm(Test_lat_intersec_depois, Test_long_intersec_depois);
        
        // % 6.3 Para os pontos de campo
        
        // [LAT_E, LONG_N, LAT_LONG_Fuso] = latlong2utm(LAT, LONG);



    }


    return 0;
}
