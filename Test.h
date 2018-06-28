/* 
 * File:   Test.h
 * Author: oriva
 *
 * Created on 20 de Agosto de 2016, 11:37
 */

#ifndef TEST_H
#define	TEST_H

#include "SOM.h"
#include "DataSet.h"
#include <fstream>

class Test {
public:
    Test();
    Test(const Test& orig);
    virtual ~Test();
    
    void leitorCSV();
    void organizeCSV();
    void acelerometroDataSet();
    void colorDataSet();
    void armInLine(); 
    void loadNetwork();
    void trainSVM();
    void loadSVM2();
    void loadSVM();
    void organizeCSVAruco();
    void arucoDataSet();
    void loadOrganizeCSVAruco();
    void loadLoadNetwork();
    void Geral(int argc, char** argv);
private:
    
    

};

#endif	/* TEST_H */

