//Para executar o codigo deve ser feito esses dois comandos passos
//  make main
//  ./main live camera.yml 0

#include "Vision.h"
#include <cstdlib>
#include <iostream>
#include "Test.h"
#include "string"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace aruco;

int main(int argc, char** argv) {
    Test test;
    
    // Vision vision(argc, argv);
    
    // //test.trainSVM();
    
    // std::string dataIn, aux, aux2;
    // aux2 = ".csv";
    // int cont = 6;

    // while(1){
    //     if(waitKey(1) == 110){

    //         aux = std::to_string(cont);
    //         dataIn = "resultados/teste";
    //         dataIn += aux;
    //         dataIn += aux2;

    //         // dataIn = "resultados/teste";
    //         // dataIn += aux2;

    //         vision.saveMovement(dataIn);
    //         //vision.record("../Samples/sample.avi");

    //         while(1){
    //             vision.calculateTagCenter();
    //             if (vision.isTargetOn()) {
    //                 vision.savePoint(vision.getCenter());
    //             }

    //             vision.show();
    //             //vision.saveVideo();
    //             if(waitKey(1) == 27){
    //                 cont++;
    //                 break;
    //             }
    //             //cout << "salvando o centro" << endl;
    //         }
    //         vision.endSaving();
    //         cout << "Salvou!" << endl;
    //         test.loadOrganizeCSVAruco();
    //         test.loadLoadNetwork();
    //         test.loadSVM();
    //     }
    //     //cout << "Esperando o 'n'!" << endl;
    // }

    //test.organizeCSV();
    //test.loadOrganizeCSVAruco();
    //test.organizeCSVAruco();
    test.trainSVM();
    //test.leitorCSV();
    //test.loadSVM();
    //test.colorDataSet(); 
    //test.acelerometroDataSet();
    //test.loadNetwork(); 
    //test.armInLine();
    //test.arucoDataSet();
    //test.Geral(argc, argv);
    return 0;
}