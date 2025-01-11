#include "Affine.hpp"
#include "Desnor.hpp"
#include "img2terrain.hpp"
#include "latlong2utm.hpp"
#include "utils/RandPerm.hpp"
#include "utils/MatrixSubSetting.hpp"
#include "RecalcRPC.hpp"
#include "StandardDeviation.hpp"
#include "mainWork.hpp"

#include <stdio.h>
#include <stdlib.h>
/*
* TODO's: change the latlong2UTM to a proj, its limited to the fuse 24
*/




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

    Eigen::MatrixXd ErrorInSample_plan(runTimes, AvailablePoints); //Matrices to error calculation
    Eigen::MatrixXd ErrorInSample_alt(runTimes, AvailablePoints);
    Eigen::MatrixXd ErrorOutSample_plan(runTimes, AvailablePoints);
    Eigen::MatrixXd ErrorOutSample_alt(runTimes, AvailablePoints);


    Eigen::MatrixXd LAT(AvailablePoints, 1);    //TODO: awating Pedro's implementation
    Eigen::MatrixXd LONG(AvailablePoints, 1);   //TODO: awating Pedro's implementation
    Eigen::MatrixXd h(AvailablePoints, 1);      //TODO: awating Pedro's implementation


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
        //TODO: NEEDS ARTHUR CHECK IMPLEMENTATION
        Coordinates Train_intersec_lat_long_h_before = SpacialInterssection(Coef_Img1, Coef_Img2, MatrixSubSetting(Line1, IndexTrain) , MatrixSubSetting(Sample1, IndexTrain),MatrixSubSetting(Line2, IndexTrain) , MatrixSubSetting(Sample2, IndexTrain), l1Correction, s1Correction, l2Correction, s2Correction, latCorrection1, longCorrection1, hCorrection1, latCorrection2, longCorrection2, hCorrection2);
        // After
        //Coordinates Train_lat_long_h_after = SpacialInterssection(Line1,IndexTrain), Sample1,IndexTrain), Line2,IndexTrain), Sample2,IndexTrain), new_a1, b1, new_c1, d1, new_a2, b2, new_c2, d2, LINE_OFF1, SAMPLE_OFF1, LAT_OFF1, LONG_OFF1, HEIGHT_OFF1, LINE_SCALE1, SAMPLE_SCALE1, LAT_SCALE1, LONG_SCALE1, HEIGHT_SCALE1, LINE_OFF2, SAMPLE_OFF2, LAT_OFF2, LONG_OFF2, HEIGHT_OFF2, LINE_SCALE2, SAMPLE_SCALE2, LAT_SCALE2, LONG_SCALE2, HEIGHT_SCALE2);
        //TODO: NEEDS ARTHUR CHECK IMPLEMENTATION
        Coordinates Train_intersec_lat_long_h_after  = SpacialInterssection(Coef_Img1_new, Coef_Img2_new, MatrixSubSetting(Line1, IndexTrain) , MatrixSubSetting(Sample1, IndexTrain),MatrixSubSetting(Line2, IndexTrain) , MatrixSubSetting(Sample2, IndexTrain), l1Correction, s1Correction, l2Correction, s2Correction, latCorrection1, longCorrection1, hCorrection1, latCorrection2, longCorrection2, hCorrection2);

        // 5.3.1 - For the tests points - before and after

        // Before
        //Coordinates Tests_lat_long_h_before = SpacialInterssection(Line1,IndexTest), Sample1,IndexTest), Line2,IndexTest), Sample2,IndexTest), a1, b1, c1, d1, a2, b2, c2, d2, LINE_OFF1, SAMPLE_OFF1, LAT_OFF1, LONG_OFF1, HEIGHT_OFF1, LINE_SCALE1, SAMPLE_SCALE1, LAT_SCALE1, LONG_SCALE1, HEIGHT_SCALE1, LINE_OFF2, SAMPLE_OFF2, LAT_OFF2, LONG_OFF2, HEIGHT_OFF2, LINE_SCALE2, SAMPLE_SCALE2, LAT_SCALE2, LONG_SCALE2, HEIGHT_SCALE2);
        //TODO: NEEDS ARTHUR CHECK IMPLEMENTATION
        Coordinates Tests_intersec_lat_long_h_before = SpacialInterssection(Coef_Img1, Coef_Img2, MatrixSubSetting(Line1, IndexTest) , MatrixSubSetting(Sample1, IndexTest),MatrixSubSetting(Line2, IndexTest) , MatrixSubSetting(Sample2, IndexTest), l1Correction, s1Correction, l2Correction, s2Correction, latCorrection1, longCorrection1, hCorrection1, latCorrection2, longCorrection2, hCorrection2);
        // After
        //Coordinates Tests_lat_long_h_after = SpacialInterssection(Line1,IndexTest), Sample1,IndexTest), Line2,IndexTest), Sample2,IndexTest), new_a1, b1, new_c1, d1, new_a2, b2, new_c2, d2, LINE_OFF1, SAMPLE_OFF1, LAT_OFF1, LONG_OFF1, HEIGHT_OFF1, LINE_SCALE1, SAMPLE_SCALE1, LAT_SCALE1, LONG_SCALE1, HEIGHT_SCALE1, LINE_OFF2, SAMPLE_OFF2, LAT_OFF2, LONG_OFF2, HEIGHT_OFF2, LINE_SCALE2, SAMPLE_SCALE2, LAT_SCALE2, LONG_SCALE2, HEIGHT_SCALE2);
        //TODO: NEEDS ARTHUR CHECK IMPLEMENTATION
        Coordinates Tests_intersec_lat_long_h_after  = SpacialInterssection(Coef_Img1_new, Coef_Img2_new, MatrixSubSetting(Line1, IndexTest) , MatrixSubSetting(Sample1, IndexTest),MatrixSubSetting(Line2, IndexTest) , MatrixSubSetting(Sample2, IndexTest), l1Correction, s1Correction, l2Correction, s2Correction, latCorrection1, longCorrection1, hCorrection1, latCorrection2, longCorrection2, hCorrection2);

        //6 Conversion of this coordinates to UTM. i think is UTM 24 - E, go into the latlong2utm function to know the 
	
	    //6.1 For the training points 
	
        //[Train_E_intersec_antes, Train_N_intersec_antes, Train_Fuso_intersec_antes] = LatLong2UTM(Train_lat_intersec_antes, Train_long_intersec_antes);
        CoordinatesUTM Train_E_N_F_intersec_before = LatLong2UTM(Train_intersec_lat_long_h_before.Lat, Train_intersec_lat_long_h_before.Long);
        
        // [Train_E_intersec_depois, Train_N_intersec_depois, Train_Fuso_intersec_depois] = latlong2utm(Train_lat_intersec_depois, Train_long_intersec_depois);
        CoordinatesUTM Train_E_N_F_intersec_after = LatLong2UTM(Train_intersec_lat_long_h_after.Lat, Train_intersec_lat_long_h_after.Long);
        
        // % 6.2 Para os pontos de teste

        // [Test_E_intersec_antes, Test_N_intersec_antes, Test_Fuso_intersec_antes] = latlong2utm(Test_lat_intersec_antes, Test_long_intersec_antes);
        CoordinatesUTM Tests_E_N_F_intersec_before = LatLong2UTM(Tests_intersec_lat_long_h_before.Lat, Tests_intersec_lat_long_h_before.Long);

        // [Test_E_intersec_depois, Test_N_intersec_depois, Test_Fuso_intersec_depois] = latlong2utm(Test_lat_intersec_depois, Test_long_intersec_depois);
        CoordinatesUTM Tests_E_N_F_intersec_after = LatLong2UTM(Tests_intersec_lat_long_h_after.Lat, Tests_intersec_lat_long_h_after.Long);

        // % 6.3 Para os pontos de campo
        
        // [LAT_E, LONG_N, LAT_LONG_Fuso] = latlong2utm(LAT, LONG);
        CoordinatesUTM LAT_LONG_to_E_N_F = LatLong2UTM(LAT, LONG); //TODO: NEEDS PEDRO IMPLEMENTATION, section 1.2 of octave file

        
        
        // % 7 Cálculo dos erro e desvio padrão do erro planimétrico e altimétrico - before and after
        //To this part i will divide it in functions
            // 7.1 Para os pontos de treinamento

        PlanimetricErrorReturn Train_desv_erro_plan_before  = PlanimetricError(LAT_LONG_to_E_N_F, Train_E_N_F_intersec_before, IndexTrain);
        
        PlanimetricErrorReturn Train_desv_erro_plan_after   = PlanimetricError(LAT_LONG_to_E_N_F, Train_E_N_F_intersec_after, IndexTrain);

        //// Altimétrico

        //Train_erro_alt_antes = abs(h(IndexTrain, :) - Train_h_intersec_antes);
        //Train_desv_erro_alt_antes = std(Train_erro_alt_antes);
        AltimetricErrorReturn Train_erro_alt_before = AltimetricError(h, Train_intersec_lat_long_h_before.Height, IndexTrain);

        //Train_erro_alt_depois = abs(h(IndexTrain, :) - Train_h_intersec_depois);
        //Train_desv_erro_alt_depois = std(Train_erro_alt_depois);
        AltimetricErrorReturn Train_erro_alt_after = AltimetricError(h, Train_intersec_lat_long_h_after.Height, IndexTrain);


        //// 7.2 Para os pontos de teste

        //    // Planimétrico

        //Test_erro_plan_antes = sqrt((LAT_E(IndexTest, :) - Test_E_intersec_antes). ^ 2 + (LONG_N(IndexTest, :) - Test_N_intersec_antes). ^ 2);
        //Test_desv_erro_plan_antes = std(Test_erro_plan_antes);
        PlanimetricErrorReturn Tests_desv_erro_plan_before = PlanimetricError(LAT_LONG_to_E_N_F, Tests_E_N_F_intersec_before, IndexTest);


        //Test_erro_plan_depois = sqrt((LAT_E(IndexTest, :) - Test_E_intersec_depois). ^ 2 + (LONG_N(IndexTest, :) - Test_N_intersec_depois). ^ 2);
        //Test_desv_erro_plan_depois = std(Test_erro_plan_depois);
        PlanimetricErrorReturn Tests_desv_erro_plan_after = PlanimetricError(LAT_LONG_to_E_N_F, Tests_E_N_F_intersec_after, IndexTest);

        //// Altimétrico

        //Test_erro_alt_antes = abs(h(IndexTest, :) - Test_h_intersec_antes);
        //Test_desv_erro_alt_antes = std(Test_erro_alt_antes);
        AltimetricErrorReturn Tests_erro_alt_before = AltimetricError(h, Tests_intersec_lat_long_h_before.Height, IndexTest);

        //Test_erro_alt_depois = abs(h(IndexTest, :) - Test_h_intersec_depois);
        //Test_desv_erro_alt_depois = std(Test_erro_alt_depois);
        AltimetricErrorReturn Tests_erro_alt_after = AltimetricError(h, Tests_intersec_lat_long_h_after.Height, IndexTest);


        //% 8 Cálculo do ErrorInSample e do ErrorOutSample planimétrico e altimétrico

        //    % ErrorInSample

        //    % Planimétrico

        //    ErrorInSample_plan = [ErrorInSample_plan; [mean(Train_erro_plan_antes), mean(Train_erro_plan_depois), std(Train_erro_plan_antes), std(Train_erro_plan_depois)] ];
              //In this case how we are using a reference of the matrix and not create a new one, we can do this way
        CalculateSampleError(ErrorInSample_plan, i, Train_desv_erro_plan_before.Error_planimetric.mean(), Train_desv_erro_plan_after.Error_planimetric.mean(), StandardDeviation(Train_desv_erro_plan_before.Error_planimetric), StandardDeviation(Train_desv_erro_plan_after.Error_planimetric));

        //% Altimétrico

        //    ErrorInSample_alt = [ErrorInSample_alt; [mean(Train_erro_alt_antes), mean(Train_erro_alt_depois), std(Train_erro_alt_antes), std(Train_erro_alt_depois)] ];
        CalculateSampleError(ErrorInSample_alt, i, Train_erro_alt_before.Error_Altimetric.mean(), Train_erro_alt_after.Error_Altimetric.mean(), StandardDeviation(Train_erro_alt_before.Error_Altimetric), StandardDeviation(Train_erro_alt_after.Error_Altimetric));

        //% ErrorOutSample

        //    % Planimétrico

        //    ErrorOutSample_plan = [ErrorOutSample_plan; [mean(Test_erro_plan_antes), mean(Test_erro_plan_depois), std(Test_erro_plan_antes), std(Test_erro_plan_depois)] ];
        CalculateSampleError(ErrorInSample_plan, i, Train_desv_erro_plan_before.Error_planimetric.mean(), Train_desv_erro_plan_after.Error_planimetric.mean(), StandardDeviation(Train_desv_erro_plan_before.Error_planimetric), StandardDeviation(Train_desv_erro_plan_after.Error_planimetric));

        //% Altimétrico

        //   ErrorOutSample_alt = [ErrorOutSample_alt; [mean(Test_erro_alt_antes), mean(Test_erro_alt_depois), std(Test_erro_alt_antes), std(Test_erro_alt_depois)] ];


    }

    //% 8 Calcula a média do ErrorInSample e do ErrorOutSample em cada coluna

    //    ErrorInSample_plan = mean(ErrorInSample_plan);
    //ErrorInSample_alt = mean(ErrorInSample_alt);
    //ErrorOutSample_plan = mean(ErrorOutSample_plan);
    //ErrorOutSample_alt = mean(ErrorOutSample_alt);

    return 0;
}

/*
* TODO: Refactor this implementation in another file
*/


PlanimetricErrorReturn PlanimetricError(CoordinatesUTM LAT_LONG_to_E_N_F, CoordinatesUTM Train_E_N_F_Intersec_x, Eigen::MatrixXd IndexTrain) {
    // Planimétrico
    PlanimetricErrorReturn calcs;
    //Train_erro_plan_antes = sqrt((LAT_E(IndexTrain, :) - Train_E_intersec_antes). ^ 2 + (LONG_N(IndexTrain, :) - Train_N_intersec_antes). ^ 2);
    Eigen::MatrixXd LAT_E   = MatrixSubSetting(LAT_LONG_to_E_N_F.East, IndexTrain);
    Eigen::MatrixXd LONG_N  = MatrixSubSetting(LAT_LONG_to_E_N_F.North, IndexTrain);
    
    Eigen::MatrixXd Train_erro_plan_antes = ( (LAT_E - Train_E_N_F_Intersec_x.East).array().pow(2) + (LONG_N - Train_E_N_F_Intersec_x.North).array().pow(2));
    Train_erro_plan_antes = Train_erro_plan_antes.array().sqrt();
   
    double Train_desv_erro_plan_antes = StandardDeviation(Train_erro_plan_antes);
    
    calcs.Error_planimetric = Train_erro_plan_antes;
    calcs.std_Error_plan    = Train_desv_erro_plan_antes;

    return calcs;
}


AltimetricErrorReturn AltimetricError(Eigen::MatrixXd h, Eigen::MatrixXd Matrix_h_intersec, Eigen::MatrixXd IndexTrain) {
    // Planimétrico
    AltimetricErrorReturn calcs;

    //Test_erro_alt_antes = abs(h(IndexTest, :) - Test_h_intersec_antes);
    Eigen::MatrixXd new_h = MatrixSubSetting(h, IndexTrain);

    Eigen::MatrixXd Test_erro_alt_antes = (new_h - Matrix_h_intersec).array().abs();
    double desv_erro_alt    = StandardDeviation(Test_erro_alt_antes);

    calcs.Error_Altimetric  = Test_erro_alt_antes;
    calcs.std_Error_alti    = desv_erro_alt;

    return calcs;
}

Eigen::MatrixXd CalculateSampleError(Eigen::MatrixXd errorMatrix, int iterator, double mean_erro_plan_before, double mean_Train_erro_plan_after, double std_Train_erro_plan_antes, double std_Train_erro_plan_depois) {

    errorMatrix(iterator, 0) = mean_erro_plan_before;
    errorMatrix(iterator, 1) = mean_Train_erro_plan_after;
    errorMatrix(iterator, 2) = std_Train_erro_plan_antes;
    errorMatrix(iterator, 3) = std_Train_erro_plan_depois;

}