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

    //test.organizeCSV();
    //test.loadOrganizeCSVAruco();
    //test.organizeCSVAruco();
    //test.trainSVM();
    //test.leitorCSV();
    //test.loadSVM();
    //test.colorDataSet(); 
    //test.acelerometroDataSet();
    //test.loadNetwork();
    test.loadSVM2();
    //test.armInLine();
    //test.arucoDataSet();
    //test.Geral(argc, argv);
    //test.dados(argc, argv);
    return 0;
}