
/* 
 * File:   main.cpp
 * Author: oriva
 *
 * Created on 20 de Agosto de 2016, 10:56
 */

//make main
//./main live camera.yml 0
#include "Vision.h"
#include <cstdlib>
#include <iostream>
#include "Test.h"
#include "string"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace aruco;

/*
 * 
 */
int main(int argc, char** argv) {
    //cout << " Testando rede SOM!" << endl;

    Test test;
    
    /*Vision vision(argc, argv);
    
    while(1){
        if(waitKey(1) == 110){
            vision.saveMovement("Samples_Data/teste.csv");
            //vision.record("../Samples/sample.avi");

            while(1){
                vision.calculateTagCenter();
                if (vision.isTargetOn()) {
                    vision.savePoint(vision.getCenter());
                }

                vision.show();
                //vision.saveVideo();
                if(waitKey(1) == 27)
                    break;
                cout << "salvando o centro" << endl;
            }
            vision.endSaving();
            cout << "Salvou!" << endl;
            test.organizeCSVAruco();
            test.loadNetwork();
        }
        cout << "Esperando o 'n'!" << endl;
    }*/
    
    
        
    //test.organizeCSV();
    //test.organizeCSVAruco();
    //test.trainSVM();
    //test.leitorCSV();
    test.loadSVM();
    //test.colorDataSet(); 
    //test.acelerometroDataSet();
    //test.loadNetwork(); 
    //test.armInLine();
    //test.arucoDataSet();
    return 0;
}