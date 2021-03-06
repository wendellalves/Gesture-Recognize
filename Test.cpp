/* 
 * File:   Test.cpp
 * Author: oriva
 * 
 * Created on 20 de Agosto de 2016, 11:37
 */

#include "CSVReader.h"
#include <fstream>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include "Test.h"
#include <string>
#include "Vision.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/ml.hpp>
#include "tcp_client.h"
#include <stdio.h>
#include <curl/curl.h>
#include <stack>
#include <list>
#include "program.h"
#include "RasBot.h"
#include <wiringPi.h>

using namespace cv::ml;

RasBot bot;

Test::Test()
{
}

Test::Test(const Test &orig)
{
}

void delay2(int max)
{
  int tmp = millis();
  while (millis() - tmp < max){}
}

void Test::leitorCSV()
{
    std::string x, y, z, iPos, jPos;
    int sizeNetwork = 10;
    //int cont = 0;

    // Creating an object of CSVWriter
    CSVReader reader("texte2.txt");

    //std::ofstream myfile;
    //myfile.open ("saida.csv");

    // Get the data from CSV File
    std::vector<std::vector<std::string>> dataList = reader.getData();

    for (int i = 1; i <= sizeNetwork * sizeNetwork; i++)
    {
        iPos = dataList[i][0];
        jPos = dataList[i][0 + 1];
        x = dataList[i][0 + 2];
        y = dataList[i][0 + 3];
        z = dataList[i][0 + 4];
        std::cout << "i = " << iPos << std::endl;
        std::cout << "j = " << jPos << std::endl;
        std::cout << "x = " << x << std::endl;
        std::cout << "y = " << y << std::endl;
        std::cout << "z = " << z << std::endl;
        std::cout << std::endl;
    }
}

void Test::organizeCSV()
{
    int cont = 0, linhas, colunas = 3;
    std::string csvBug = "data/Acelerometro/esquerda/esquerda10.csv";
    std::string csvOrganizado = "data/Acelerometro/newEsquerda/esquerda10.csv";

    // Creating an object of CSVWriter
    CSVReader reader(csvBug);

    std::ofstream myfile;
    myfile.open(csvOrganizado);

    // Get the data from CSV File
    std::vector<std::vector<std::string>> dataList = reader.getData();

    linhas = dataList.size() / 3;

    myfile << linhas << " " << colunas << "\n";

    for (std::vector<std::string> vec : dataList)
    {
        for (std::string data : vec)
        {
            myfile << data;
            myfile << " ";
            cont++;
            if (cont == 3)
            {
                myfile << "\n";
                cont = 0;
            }
        }
    }
    //std::cout << dataList.size();

    myfile.close();
}

void Test::loadOrganizeCSVAruco()
{
    int cont = 0, linhas, colunas = 2;
    std::string arquivoIn, arquivoOut;

    arquivoIn = "data/CtrlRobo/CtrlRobo.csv";
    arquivoOut = "data/CtrlRobo/CtrlRoboOrganizado.csv";
    //arquivoIn = "resultados/teste.csv";
    //arquivoOut = "resultados/testeIn.csv";
    //arquivoIn = "data/dadosAruco/DE.csv";
    //arquivoOut = "data/dadosAruco/DEOrganizado.csv";

    // Creating an object of CSVWriter
    CSVReader reader(arquivoIn);

    std::ofstream myfile;
    myfile.open(arquivoOut);

    // Get the data from CSV File
    std::vector<std::vector<std::string>> dataList = reader.getData();

    linhas = dataList.size();

    myfile << linhas << " " << colunas << "\n";

    for (std::vector<std::string> vec : dataList)
    {
        for (std::string data : vec)
        {
            myfile << data;
            myfile << " ";
            cont++;
            if (cont == 2)
            {
                myfile << "\n";
                cont = 0;
            }
        }
    }
    //std::cout << dataList.size();

    myfile.close();
}

void Test::organizeCSVAruco()
{
    int cont = 0, linhas, colunas = 2;
    std::string arquivoIn, arquivoOut, aux, aux2;
    aux2 = ".csv";

    for (int i = 1; i < 26; i++)
    {
        aux = std::to_string(i);
        arquivoIn = "data/CtrlRobo/Loop/loop";
        arquivoIn += aux;
        arquivoIn += aux2;

        arquivoOut = "data/CtrlRobo/DEFTNew/loop";
        arquivoOut += aux;
        arquivoOut += aux2;

        // Creating an object of CSVWriter
        CSVReader reader(arquivoIn);

        std::ofstream myfile;
        myfile.open(arquivoOut);

        // Get the data from CSV File
        std::vector<std::vector<std::string>> dataList = reader.getData();

        linhas = dataList.size();

        myfile << linhas << " " << colunas << "\n";

        for (std::vector<std::string> vec : dataList)
        {
            for (std::string data : vec)
            {
                myfile << data;
                myfile << " ";
                cont++;
                if (cont == 2)
                {
                    myfile << "\n";
                    cont = 0;
                }
            }
        }
        //std::cout << dataList.size();

        myfile.close();
    }
}

void Test::acelerometroDataSet()
{
    std::string fileData = "data/Acelerometro/esquerdaDireita.csv";

    SOM som(10);
    DataSet *data = new DataSet(fileData);
    data->show();

    som.setDataSet(data);

    float maxColorInitialValue = 0.02;
    som.initializeNodes(3, true, maxColorInitialValue);

    int iterations = 150;

    // Execute many iterations
    int i = 0;
    som.printNodes();
    while (i < (iterations))
    {
        som.executeOneIt();
        i++;
        som.printNodes();

        som.saveNodes("visualization/esquerdaDireita/", "i,j,x,y,z", false);
    }

    //som.printNodes();
    som.saveNodes("visualization/esquerdaDireita/", "i,j,x,y,z", false);

    std::cout << "Iteractions executed: " << iterations << std::endl;

    delete data;
}

void Test::arucoDataSet()
{
    std::string fileData = "data/CtrlRobo/CtrlRoboOrganizado.csv";

    SOM som(10);
    DataSet *data = new DataSet(fileData);
    data->show();

    som.setDataSet(data);

    float maxColorInitialValue = 0.02;
    som.initializeNodes(2, true, maxColorInitialValue);

    int iterations = 2500000;

    // Execute many iterations
    int i = 0;
    //som.printNodes();
    while (i < (iterations))
    {
        som.executeOneIt();
        i++;
        if (i % 100000 == 0)
        {
            //som.printNodes();
            som.saveNodes("visualization/treinamentoAruco/", "i,j,x,y", false);
        }
    }

    //som.printNodes(true);
    som.saveNodes("visualization/treinamentoAruco/", "i,j,x,y", false);

    std::cout << "Iteractions executed: " << iterations << std::endl;

    delete data;
}

void Test::colorDataSet()
{
    std::string fileData = "data/Dados/direitaType2.csv";

    SOM som(10);
    DataSet *data = new DataSet(fileData);
    data->show();

    som.setDataSet(data);

    float maxColorInitialValue = 0.02;
    som.initializeNodes(3, true, maxColorInitialValue);

    int iterations = 150;

    // Execute many iterations
    int i = 0;
    som.printNodes();
    while (i < (iterations - 1))
    {
        som.executeOneIt();
        i++;
        som.printNodes();

        som.saveNodes("visualization/iterations4/", "x,y,r,g,b", false);
    }
    //som.executeOneIt1();
    som.printNodes();
    som.saveNodes("visualization/iterations4/", "x,y,r,g,b", false);

    std::cout << "Iteractions executed: " << iterations << std::endl;

    delete data;
}

void Test::armInLine()
{
    std::string fileData = "data/braco_em_linha.txt";
    SOM som(12);
    DataSet *data = new DataSet(fileData);
    data->show();

    som.setDataSet(data);

    float maxFeatureInitialValue = 0.01;
    som.initializeNodes(4, true, maxFeatureInitialValue);

    int iterations = 250;

    // Execute many iterations
    int i = 0;
    som.saveNodes("/visualization/web/data/arm_in_line_", "x, y, beta, gamma, rx, ry", false);
    while (i < iterations)
    {
        som.executeOneIt();
        i++;
        som.saveNodes("/visualization/web/data/arm_in_line_", "x, y, beta, gamma, rx, ry", false);
    }
    std::cout << "Iteractions executed: " << iterations << std::endl;

    delete data;
}

void Test::loadLoadNetwork()
{
    // usar o dataset
    int tam = 10, iImagem, jImagem;
    int tamImagem = tam * 80; // para uma resolucao maior
    cv::Mat image(tamImagem, tamImagem, 0);
    cv::Mat imagem(tam, tam, 0);
    std::string posImagem;
    SOM som(tam);
    DataSet data;
    Sample *s;
    //Node* vencedor;
    //std::vector <Node*> vencedores; // v = find  ...

    std::string dataIn, imageOutVisual, imageOutTrain;

    //int imagem[tamImagem][tamImagem];

    som.loadNetworkAruco("visualization/treinamentoAruco/1500000.csv", tam);

    for (int i = 0; i < tamImagem; i++)
    {
        for (int j = 0; j < tamImagem; j++)
        {
            //imagem[i][j] = 0;
            image.at<uchar>(i, j) = 0;
        }
    }

    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            imagem.at<uchar>(i, j) = 0;
        }
    }

    dataIn = "resultados/testeIn.csv";

    imageOutVisual = "resultados/visual.jpg";

    imageOutTrain = "resultados/teste.jpg";

    data.loadDataFromFile(dataIn);

    s = data.getRandomSample();
    som.findWinner(s, iImagem, jImagem);

    while (!(data.getRandomSample(s)))
    {
        som.findWinner(s, iImagem, jImagem);

        imagem.at<uchar>(iImagem, jImagem) = 255;

        for (int i = iImagem * 80; i < (iImagem * 80 + 80); i++)
        {
            for (int j = jImagem * 80; j < (jImagem * 80 + 80); j++)
            {
                image.at<uchar>(i, j) = 255;
            }
        }
    }

    //cv::imshow("Nodes", image);
    cv::imwrite(imageOutVisual, image);
    cv::imwrite(imageOutTrain, imagem);
    //cv::waitKey();
}

void Test::loadNetwork()
{
    // usar o dataset
    int tam = 10, iImagem, jImagem;
    int tamImagem = tam * 80; // para uma resolucao maior
    cv::Mat image(tamImagem, tamImagem, 0);
    cv::Mat imagem(tam, tam, 0);
    std::string posImagem;
    SOM som(tam);
    DataSet data;
    Sample *s;
    //Node* vencedor;
    //std::vector <Node*> vencedores; // v = find  ...

    std::string dataIn, imageOutVisual, imageOutTrain, aux, aux2, aux3;
    aux2 = ".csv";
    aux3 = ".jpg";

    //int imagem[tamImagem][tamImagem];

    som.loadNetworkAruco("visualization/treinamentoAruco/2500000.csv", tam);

    for (int i = 1; i < 26; i++)
    {
        for (int i = 0; i < tamImagem; i++)
        {
            for (int j = 0; j < tamImagem; j++)
            {
                //imagem[i][j] = 0;
                image.at<uchar>(i, j) = 0;
            }
        }

        for (int i = 0; i < tam; i++)
        {
            for (int j = 0; j < tam; j++)
            {
                imagem.at<uchar>(i, j) = 0;
            }
        }

        aux = std::to_string(i);
        dataIn = "data/CtrlRobo/DEFTNew/loop";
        dataIn += aux;
        dataIn += aux2;

        imageOutVisual = "resultadosSom/visualizar/loopVisual";
        imageOutVisual += aux;
        imageOutVisual += aux3;

        imageOutTrain = "resultadosSom/treinar/loopTrain";
        imageOutTrain += aux;
        imageOutTrain += aux3;

        data.loadDataFromFile(dataIn);

        s = data.getRandomSample();
        som.findWinner(s, iImagem, jImagem);

        while (!(data.getRandomSample(s)))
        {
            som.findWinner(s, iImagem, jImagem);

            imagem.at<uchar>(iImagem, jImagem) = 255;

            for (int i = iImagem * 80; i < (iImagem * 80 + 80); i++)
            {
                for (int j = jImagem * 80; j < (jImagem * 80 + 80); j++)
                {
                    image.at<uchar>(i, j) = 255;
                }
            }
        }

        //cv::imshow("Nodes", image);
        cv::imwrite(imageOutVisual, image);
        cv::imwrite(imageOutTrain, imagem);
    }
    //cv::waitKey();
}

void Test::trainSVM()
{
    int lin = 10, col = 10;
    int qntImg = 175, tamImg = lin * col;
    int labels[qntImg];
    std::vector<cv::Mat> imagem(qntImg);

    std::string dataIn, aux, aux2;
    aux2 = ".jpg";

    for (int i = 1; i < qntImg + 1; i++)
    {
        if (i < 26)
        {
            aux = std::to_string(i);
            dataIn = "resultadosSom/treinar/direitaTrain";
            dataIn += aux;
            dataIn += aux2;
            imagem[i - 1] = cv::imread(dataIn, 0);
            labels[i - 1] = 1;
            std::cout << dataIn << std::endl;
        }
        else if (i < 51)
        {
            aux = std::to_string(i - 25);
            dataIn = "resultadosSom/treinar/esquerdaTrain";
            dataIn += aux;
            dataIn += aux2;
            imagem[i - 1] = cv::imread(dataIn, 0);
            labels[i - 1] = -1;
            std::cout << dataIn << std::endl;
        }
        else if (i < 76)
        {
            aux = std::to_string(i - 50);
            dataIn = "resultadosSom/treinar/frenteTrain";
            dataIn += aux;
            dataIn += aux2;
            imagem[i - 1] = cv::imread(dataIn, 0);
            labels[i - 1] = 2;
        }
        else if (i < 101)
        {
            aux = std::to_string(i - 75);
            dataIn = "resultadosSom/treinar/trasTrain";
            dataIn += aux;
            dataIn += aux2;
            imagem[i - 1] = cv::imread(dataIn, 0);
            labels[i - 1] = -2;
        }
        else if (i < 126)
        {
            aux = std::to_string(i - 100);
            dataIn = "resultadosSom/treinar/fecharTrain";
            dataIn += aux;
            dataIn += aux2;
            imagem[i - 1] = cv::imread(dataIn, 0);
            labels[i - 1] = 3;
        }
        else if (i < 151)
        {
            aux = std::to_string(i - 125);
            dataIn = "resultadosSom/treinar/ifTrain";
            dataIn += aux;
            dataIn += aux2;
            imagem[i - 1] = cv::imread(dataIn, 0);
            labels[i - 1] = -3;
        }
        else if (i < 176)
        {
            aux = std::to_string(i - 150);
            dataIn = "resultadosSom/treinar/loopTrain";
            dataIn += aux;
            dataIn += aux2;
            imagem[i - 1] = cv::imread(dataIn, 0);
            labels[i - 1] = 4;
        }
    }

    int ii = 0;
    cv::Mat matImage(qntImg, tamImg, CV_32FC1);
    for (int k = 0; k < qntImg; k++)
    {
        for (int i = 0; i < lin; i++)
        {
            for (int j = 0; j < col; j++)
            {
                matImage.at<float>(k, ii++) = imagem[k].at<uchar>(i, j);
            }
        }
        ii = 0;
    }

    //! [setup2]
    //cv::Mat trainingDataMat(qntImg, 2, CV_32FC1, matImage);
    cv::Mat labelsMat(qntImg, 1, CV_32SC1, labels);
    //! [setup2]

    // Train the SVM
    //! [init]
    cv::Ptr<SVM> svm = SVM::create();
    svm->setType(SVM::C_SVC);
    svm->setKernel(SVM::POLY);
    svm->setDegree(3);
    //svm->setC(1);
    //svm->setGamma(0.50625);
    //svm->setCoef0(0.6);
    //svm->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER, 100000, 1e-6));
    //! [init]
    //! [train]
    //svm->train(matImage, ROW_SAMPLE, labelsMat);
    svm->trainAuto(matImage, ROW_SAMPLE, labelsMat);

    // store its knowledge in a yaml file
    svm->save("knowledge.yml");
    //! [train]
    //cv::imshow("teste", matImage);
    cv::waitKey(0);
}

void Test::loadSVM2()
{
    int ii = 0;
    cv::Mat imagem;
    imagem = cv::imread("resultadosSom/treinar/direitaTrain2.jpg", 0);
    //imagem[1] = cv::imread("direitaTrain2.jpg", 0);
    //imagem[2] = cv::imread("frenteTrain4.jpg", 0);
    int lin = 10, col = 10;
    int tamImg = lin * col;

    std::string dataIn, aux, aux2;
    aux2 = ".jpg";

    cv::Mat imagem1D(1, tamImg, CV_32FC1);
    cv::Ptr<SVM> svm;
    svm = cv::ml::StatModel::load<cv::ml::SVM>("knowledge.yml");

    //dataIn = "testar/trasTrain";
    //dataIn += aux2;

    //imagem = cv::imread(dataIn, 0);

    std::cout << dataIn << " - ";
    std::cout << "Esperado: -2 -     Recebido: ";

    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            imagem1D.at<float>(0, ii++) = imagem.at<uchar>(i, j);
        }
    }
    int predicted = svm->predict(imagem1D);
    std::cout //<< std::endl
        << predicted << std::endl
        << std::endl;

    // std::cout << "C = " << svm->getC() << std::endl;
    // std::cout << "Gamma = " << svm->getGamma() << std::endl;
    // std::cout << "Degree = " << svm->getDegree() << std::endl;
    // std::cout << "Nu = " << svm->getNu() << std::endl;
    // std::cout << "Coef0 = " << svm->getCoef0() << std::endl;

    if (predicted == 1)
        std::cout << std::endl
                  << "Direita" << std::endl
                  << std::endl;
    else if (predicted == -1)
        std::cout << std::endl
                  << "Esquerda" << std::endl
                  << std::endl;
    else if (predicted == 2)
        std::cout << std::endl
                  << "Frente" << std::endl
                  << std::endl;
    else if (predicted == -2)
        std::cout << std::endl
                  << "Tras" << std::endl
                  << std::endl;
    else if (predicted == 3)
        std::cout << std::endl
                  << "Fechar" << std::endl
                  << std::endl;
    else if (predicted == -3)
        std::cout << std::endl
                  << "If" << std::endl
                  << std::endl;
    else if (predicted == 4)
        std::cout << std::endl
                  << "Loop" << std::endl
                  << std::endl;
}

void Test::loadSVM()
{
    int ii = 0;
    cv::Mat imagem = cv::imread("resultados/teste.jpg", 0);
    int lin = imagem.rows, col = imagem.cols;
    int tamImg = lin * col;

    cv::Mat imagem1D(1, tamImg, CV_32FC1);
    cv::Ptr<SVM> svm;
    svm = cv::Algorithm::load<SVM>("knowledge.yml");

    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            imagem1D.at<float>(0, ii++) = imagem.at<uchar>(i, j);
        }
    }

    int predicted = svm->predict(imagem1D);

    std::cout << std::endl
              << "Number -> " << predicted << std::endl
              << std::endl;

    if (predicted == 1)
        std::cout << std::endl
                  << "Direita" << std::endl
                  << std::endl;
    else if (predicted == -1)
        std::cout << std::endl
                  << "Esquerda" << std::endl
                  << std::endl;
    else if (predicted == 2)
        std::cout << std::endl
                  << "Frente" << std::endl
                  << std::endl;
    else
        std::cout << std::endl
                  << "Tras" << std::endl
                  << std::endl;
    //std::cout << std::endl
    //         << "Number -> " << predicted << std::endl
    //        << std::endl;
    cv::imshow("saida", imagem);
}

void Test::Geral(int argc, char **argv)
{
    //Test test;

    Vision vision(argc, argv);

    //test.trainSVM();

    std::string dataIn, aux, aux2, dataOut, auxOut;
    dataOut = "192.168.0.20/";
    //dataOut = "10.6.3.105/";

    tcp_client c;
    //c.conn("192.168.0.20", 80);
    //c.conn("10.6.3.105", 80);
    //aux2 = ".csv";
    int cont = 1;
    std::list<char> listaComandos;

    while (1)
    {
        if (cv::waitKey(1) == 110) // Press "n"
        {

            //aux = std::to_string(cont);
            dataIn = "resultados/teste.csv";
            //dataIn += aux;
            //dataIn += aux2;

            // dataIn = "resultados/teste";
            // dataIn += aux2;

            vision.saveMovement(dataIn);
            //vision.record("../Samples/sample.avi");

            while (1)
            {
                vision.calculateTagCenter();
                if (vision.isTargetOn())
                {
                    vision.savePoint(vision.getCenter());
                }

                vision.show();
                //vision.saveVideo();
                if (cv::waitKey(1) == 27) //Press "Esc"
                {
                    cont++;
                    break;
                }
                //cout << "salvando o centro" << endl;
            }
            vision.endSaving();
            std::cout << "Salvou!" << std::endl;
            int cont = 0, linhas, colunas = 2;
            std::string arquivoIn, arquivoOut;

            arquivoIn = "resultados/teste.csv";
            arquivoOut = "resultados/testeIn.csv";
            //arquivoIn = "data/dadosAruco/DE.csv";
            //arquivoOut = "data/dadosAruco/DEOrganizado.csv";

            // Creating an object of CSVWriter
            CSVReader reader(arquivoIn);

            std::ofstream myfile;
            myfile.open(arquivoOut);

            // Get the data from CSV File
            std::vector<std::vector<std::string>> dataList = reader.getData();

            linhas = dataList.size();

            myfile << linhas << " " << colunas << "\n";

            for (std::vector<std::string> vec : dataList)
            {
                for (std::string data : vec)
                {
                    myfile << data;
                    myfile << " ";
                    cont++;
                    if (cont == 2)
                    {
                        myfile << "\n";
                        cont = 0;
                    }
                }
            }
            //std::cout << dataList.size();

            myfile.close();

            int tam = 10, iImagem, jImagem;
            int tamImagem = tam * 80; // para uma resolucao maior
            cv::Mat image(tamImagem, tamImagem, 0);
            cv::Mat imagem(tam, tam, 0);
            std::string posImagem;
            SOM som(tam);
            DataSet data;
            Sample *s;
            //Node* vencedor;
            //std::vector <Node*> vencedores; // v = find  ...

            std::string dataInSOM, imageOutVisual, imageOutTrain;

            //int imagem[tamImagem][tamImagem];

            som.loadNetworkAruco("visualization/treinamentoAruco/2500000.csv", tam);

            for (int i = 0; i < tamImagem; i++)
            {
                for (int j = 0; j < tamImagem; j++)
                {
                    //imagem[i][j] = 0;
                    image.at<uchar>(i, j) = 0;
                }
            }

            for (int i = 0; i < tam; i++)
            {
                for (int j = 0; j < tam; j++)
                {
                    imagem.at<uchar>(i, j) = 0;
                }
            }

            dataInSOM = "resultados/testeIn.csv";

            imageOutVisual = "resultados/visual.jpg";

            imageOutTrain = "resultados/teste.jpg";

            data.loadDataFromFile(dataInSOM);

            s = data.getRandomSample();
            som.findWinner(s, iImagem, jImagem);

            while (!(data.getRandomSample(s)))
            {
                som.findWinner(s, iImagem, jImagem);

                imagem.at<uchar>(iImagem, jImagem) = 255;

                for (int i = iImagem * 80; i < (iImagem * 80 + 80); i++)
                {
                    for (int j = jImagem * 80; j < (jImagem * 80 + 80); j++)
                    {
                        image.at<uchar>(i, j) = 255;
                    }
                }
            }

            //cv::imshow("Nodes", image);
            cv::imwrite(imageOutVisual, image);
            cv::imwrite(imageOutTrain, imagem);
            //cv::waitKey();

            int ii = 0;
            cv::Mat imagem2 = cv::imread("resultados/teste.jpg", 0);
            int lin = imagem2.rows, col = imagem2.cols;
            int tamImg = lin * col;

            cv::Mat imagem1D(1, tamImg, CV_32FC1);
            cv::Ptr<SVM> svm;
            svm = cv::Algorithm::load<SVM>("knowledge.yml");

            for (int i = 0; i < lin; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    imagem1D.at<float>(0, ii++) = imagem2.at<uchar>(i, j);
                }
            }

            int predicted = svm->predict(imagem1D);

            //tcp_client c;

            //connect to host
            //c.conn("192.168.0.20", 80);
            //dataOut = "192.168.0.20/";
            //c.conn("10.6.3.105", 80);
            //dataOut = "10.6.3.105/";

            std::cout << predicted << std::endl;

            if (predicted == 1)
            {
                std::cout << std::endl
                          << "Direita" << std::endl
                          << std::endl;
                //listaComandos.push_back('d');
                auxOut = 'd';
                dataOut += auxOut;
                //send some data
                std::cout << std::endl
                          << dataOut << std::endl
                          << std::endl;
            }
            else if (predicted == -1)
            {
                std::cout << std::endl
                          << "Esquerda" << std::endl
                          << std::endl;
                //listaComandos.push_back('e');
                auxOut = 'e';
                dataOut += auxOut;
            }
            else if (predicted == 2)
            {
                std::cout << std::endl
                          << "Frente" << std::endl
                          << std::endl;
                //listaComandos.push_back('f');
                auxOut = 'f';
                dataOut += auxOut;
            }
            else if (predicted == -2)
            {
                std::cout << std::endl
                          << "Tras" << std::endl
                          << std::endl;
                //listaComandos.push_back('t');
                auxOut = 't';
                dataOut += auxOut;
            }
            else if (predicted == 3)
            {
                std::cout << std::endl
                          << "Close" << std::endl
                          << std::endl;
                listaComandos.push_back('c');
                //std::cout << "Enviar comandos" << std::endl;
                auxOut = 'c';
                dataOut += auxOut;

                //c.conn("10.6.3.105", 80);
                c.conn("192.168.0.20", 80);
                c.send_data(dataOut);

                std::cout << std::endl
                          << dataOut << std::endl
                          << std::endl;
                std::cout << std::endl
                          << "ENVIADO" << std::endl
                          << std::endl;

                //dataOut = "10.6.3.105/";
                dataOut = "192.168.0.20/";
            }
            else if (predicted == -3)
            {
                std::cout << std::endl
                          << "If" << std::endl
                          << std::endl;
                //listaComandos.push_back('i');
                auxOut = 'i';
                dataOut += auxOut;
            }
            else
            {
                std::cout << std::endl
                          << "Loop" << std::endl
                          << std::endl;
                //listaComandos.push_back('l');
                auxOut = 'l';
                dataOut += auxOut;
            }
        }
        //cout << "Esperando o 'n'!" << endl;
    }
    //Enviar a lista para o bluetooth
}

void Test::dados(int argc, char **argv)
{

    Vision vision(argc, argv);

    std::string dataIn, aux, aux2;
    aux2 = ".csv";
    int cont = 1;

    while (1)
    {
        if (cv::waitKey(1) == 110)
        {

            aux = std::to_string(cont);
            dataIn = "data/CtrlRobo/Fechar/fechar";
            dataIn += aux;
            dataIn += aux2;

            vision.saveMovement(dataIn);

            while (1)
            {
                vision.calculateTagCenter();
                if (vision.isTargetOn())
                {
                    vision.savePoint(vision.getCenter());
                }

                vision.show();
                //vision.saveVideo();
                if (cv::waitKey(1) == 27)
                {
                    cont++;
                    std::cout << "Salvou o " << dataIn << std::endl;
                    //std::cout << cont << std::endl;
                    break;
                }
                else if (cv::waitKey(1) == 32)
                {
                    std::cout << "A proxima vai sobrescrever o " << dataIn << std::endl;
                    //std::cout << cont << std::endl;
                    break;
                }
            }
            vision.endSaving();
            std::cout << "Salvou!" << std::endl;
        }
    }
}
void Test::tcpClient()
{
    tcp_client c;
    std::string host;

    std::cout << "Enter hostname : ";
    host = "192.168.0.20";

    //connect to host
    c.conn(host, 80);

    //send some data
    c.send_data("http://192.168.0.20/dc");

    //receive and echo reply
    std::cout << "----------------------------\n\n";
    std::cout << c.receive(1024);
    std::cout << "\n\n----------------------------\n\n";
}
void Test::udp_client()
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "http://10.0.0.103/gpio/1"); //(1)

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }
}

void Test::GeralUDP(int argc, char **argv)
{
    //Test test;

    Vision vision(argc, argv);

    CURL *curl;
    CURLcode res;

    //test.trainSVM();

    std::string dataIn, aux, aux2, dataOut, dataOutAux, identacao, listaComandos;
    char auxOut;
    std::stack<char> blocos;
    //dataOut = "192.168.0.20/";
    dataOut = "http://10.0.0.101/";
    //dataOut = new std::string(&argv[3]);

    //aux2 = ".csv";
    int cont = 1, contLoop = 0, contIf = 0;
    //std::list<char> listaComandos;
    dataIn = "resultados/teste.csv";
    //vision.saveMovement(dataIn);
    while (1)
    {
        vision.calculateTagCenter();
        if (vision.isTargetOn())
        {

            vision.show();
            //std::cout << vision.getCenter().x << " " << vision.getCenter().y << std::endl;
            if ((300 < vision.getCenter().x && vision.getCenter().x < 340) &&
                (220 < vision.getCenter().y && vision.getCenter().y < 260) /*cv::waitKey(1) == 110*/) // Press "n"
            {
                //std::cout << "Iniciou a gravação" << std::endl;
                vision.setIniciou(true);
                //aux = std::to_string(cont);

                //dataIn += aux;
                //dataIn += aux2;

                // dataIn = "resultados/teste";
                // dataIn += aux2;

                vision.saveMovement(dataIn);

                //vision.record("../Samples/sample.avi");

                while (1)
                {
                    vision.calculateTagCenter();

                    if (vision.isTargetOn())
                    {
                        vision.savePoint(vision.getCenter());
                    }

                    vision.show();
                    //vision.saveVideo();
                    //std::cout << vision.getCenter().x << " " << vision.getCenter().y << std::endl;
                    if (((10 < vision.getCenter().x && vision.getCenter().x < 50) ||
                         (590 < vision.getCenter().x && vision.getCenter().x < 630)) ||
                        ((10 < vision.getCenter().y && vision.getCenter().y < 50) ||
                         (430 < vision.getCenter().y && vision.getCenter().y < 470))) //cv::waitKey(1) == 27) //Press "Esc"
                    {

                        cont++;
                        break;
                    }
                    //cout << "salvando o centro" << endl;
                }

                vision.endSaving();
                std::cout << "Salvou!" << std::endl;
                int cont = 0, linhas, colunas = 2;
                std::string arquivoIn, arquivoOut;

                arquivoIn = "resultados/teste.csv";
                arquivoOut = "resultados/testeIn.csv";
                //arquivoIn = "data/dadosAruco/DE.csv";
                //arquivoOut = "data/dadosAruco/DEOrganizado.csv";

                // Creating an object of CSVWriter
                CSVReader reader(arquivoIn);

                std::ofstream myfile;
                myfile.open(arquivoOut);

                // Get the data from CSV File
                std::vector<std::vector<std::string>> dataList = reader.getData();

                linhas = dataList.size();

                myfile << linhas << " " << colunas << "\n";

                for (std::vector<std::string> vec : dataList)
                {
                    for (std::string data : vec)
                    {
                        myfile << data;
                        myfile << " ";
                        cont++;
                        if (cont == 2)
                        {
                            myfile << "\n";
                            cont = 0;
                        }
                    }
                }
                //std::cout << dataList.size();

                myfile.close();

                int tam = 10, iImagem, jImagem;
                int tamImagem = tam * 80; // para uma resolucao maior
                cv::Mat image(tamImagem, tamImagem, 0);
                cv::Mat imagem(tam, tam, 0);
                std::string posImagem;
                SOM som(tam);
                DataSet data;
                Sample *s;
                //Node* vencedor;
                //std::vector <Node*> vencedores; // v = find  ...

                std::string dataInSOM, imageOutVisual, imageOutTrain;

                //int imagem[tamImagem][tamImagem];

                som.loadNetworkAruco("visualization/treinamentoAruco/2500000.csv", tam);

                for (int i = 0; i < tamImagem; i++)
                {
                    for (int j = 0; j < tamImagem; j++)
                    {
                        //imagem[i][j] = 0;
                        image.at<uchar>(i, j) = 0;
                    }
                }

                for (int i = 0; i < tam; i++)
                {
                    for (int j = 0; j < tam; j++)
                    {
                        imagem.at<uchar>(i, j) = 0;
                    }
                }

                dataInSOM = "resultados/testeIn.csv";

                imageOutVisual = "resultados/visual.jpg";

                imageOutTrain = "resultados/teste.jpg";

                data.loadDataFromFile(dataInSOM);

                s = data.getRandomSample();
                som.findWinner(s, iImagem, jImagem);

                while (!(data.getRandomSample(s)))
                {
                    som.findWinner(s, iImagem, jImagem);

                    imagem.at<uchar>(iImagem, jImagem) = 255;

                    for (int i = iImagem * 80; i < (iImagem * 80 + 80); i++)
                    {
                        for (int j = jImagem * 80; j < (jImagem * 80 + 80); j++)
                        {
                            image.at<uchar>(i, j) = 255;
                        }
                    }
                }

                //cv::imshow("Nodes", image);
                cv::imwrite(imageOutVisual, image);
                cv::imwrite(imageOutTrain, imagem);
                //cv::waitKey();

                int ii = 0;
                cv::Mat imagem2 = cv::imread("resultados/teste.jpg", 0);
                int lin = imagem2.rows, col = imagem2.cols;
                int tamImg = lin * col;

                cv::Mat imagem1D(1, tamImg, CV_32FC1);
                cv::Ptr<SVM> svm;
                svm = cv::Algorithm::load<SVM>("knowledge.yml");

                for (int i = 0; i < lin; i++)
                {
                    for (int j = 0; j < col; j++)
                    {
                        imagem1D.at<float>(0, ii++) = imagem2.at<uchar>(i, j);
                    }
                }

                int predicted = svm->predict(imagem1D);

                //tcp_client c;

                //connect to host
                //c.conn("192.168.0.20", 80);
                //dataOut = "192.168.0.20/";
                //c.conn("10.6.3.105", 80);
                //dataOut = "10.6.3.105/";

                //std::cout << predicted << std::endl;

                if (predicted == 1)
                {
                    listaComandos += "\n";
                    listaComandos += identacao;
                    listaComandos += "Direita";
                    std::cout << listaComandos << std::endl;
                    //listaComandos.push_back('d');
                    auxOut = 'd';
                    dataOut += auxOut;
                    //send some data
                    // std::cout << dataOut << std::endl
                    //           << std::endl;
                }
                else if (predicted == -1)
                {
                    listaComandos += "\n";
                    listaComandos += identacao;
                    listaComandos += "Esquerda";
                    std::cout << listaComandos << std::endl;
                    //listaComandos.push_back('e');
                    auxOut = 'e';
                    dataOut += auxOut;
                    // std::cout << std::endl
                    //           << dataOut << std::endl
                    //           << std::endl;
                }
                else if (predicted == 2)
                {
                    listaComandos += "\n";
                    listaComandos += identacao;
                    listaComandos += "Frente";
                    std::cout << listaComandos << std::endl;
                    //listaComandos.push_back('f');
                    auxOut = 'f';
                    dataOut += auxOut;
                    // std::cout << std::endl
                    //           << dataOut << std::endl
                    //           << std::endl;
                }
                else if (predicted == -2)
                {
                    listaComandos += "\n";
                    listaComandos += identacao;
                    listaComandos += "Tras";
                    std::cout << listaComandos << std::endl;
                    //listaComandos.push_back('t');
                    auxOut = 't';
                    dataOut += auxOut;
                    // std::cout << std::endl
                    //           << dataOut << std::endl
                    //           << std::endl;
                }
                else if (predicted == 3)
                {
                    auxOut = 'c';
                    dataOut += auxOut;
                    // std::cout << std::endl
                    //           << dataOut << std::endl
                    //           << std::endl;

                    if (contLoop == 0 && contIf == 0)
                    {
                        char teste[dataOut.length()];
                        strcpy(teste, dataOut.c_str());
                        identacao.clear();

                        curl = curl_easy_init();
                        if (curl)
                        {
                            curl_easy_setopt(curl, CURLOPT_URL, teste); //(1)

                            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

                            res = curl_easy_perform(curl);

                            if (res != CURLE_OK)
                                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

                            curl_easy_cleanup(curl);
                        }

                        std::cout << std::endl
                                  << "ENVIADO" << std::endl
                                  << std::endl;

                        identacao.clear();
                        dataOut = "http://10.0.0.101/";
                    }
                    else
                    {
                        identacao.erase(0, 1);
                        if (blocos.top() == 'l')
                        {
                            blocos.pop();
                            contLoop--;
                        }
                        else if (blocos.top() == 'i')
                        {
                            blocos.pop();
                            contIf--;
                        }
                    }
                }
                else if (predicted == -3)
                {
                    contIf++;
                    listaComandos += "\n";
                    listaComandos += identacao;
                    listaComandos += "If";
                    std::cout << listaComandos << std::endl;
                    auxOut = 'i';
                    dataOut += auxOut;
                    // std::cout << std::endl
                    //           << dataOut << std::endl
                    //           << std::endl;
                    identacao.insert(0, "\t");
                    blocos.push(auxOut);
                }
                else if (predicted == 4)
                {
                    listaComandos += "\n";
                    listaComandos += identacao;
                    listaComandos += "Loop";
                    std::cout << listaComandos << std::endl;
                    //listaComandos.push_back('l');
                    auxOut = 'l';
                    dataOut += auxOut;
                    contLoop++;
                    // std::cout << std::endl
                    //           << "Abriu Loop" << contLoop << std::endl
                    //           << std::endl;
                    // std::cout << std::endl
                    //           << dataOut << std::endl
                    //           << std::endl;
                    identacao.insert(0, "\t");
                    blocos.push(auxOut);
                }
            }
        }
    }
}

void Test::GeralRasBot(int argc, char **argv)
{
    //Test test;

    Vision vision(argc, argv);

    CURL *curl;
    CURLcode res;

    //test.trainSVM();

    std::string dataIn, aux, aux2, dataOut, dataOutAux, identacao, listaComandos;
    char auxOut;
    std::stack<char> blocos;
    std::list<char> programacao;

    int cont = 1, contLoop = 0, contIf = 0;
    dataIn = "resultados/teste.csv";

    while (1)
    {
        vision.calculateTagCenter();
        if (vision.isTargetOn())
        {

            vision.show();
            //std::cout << vision.getCenter().x << " " << vision.getCenter().y << std::endl;
            if ((300 < vision.getCenter().x && vision.getCenter().x < 340) &&
                (220 < vision.getCenter().y && vision.getCenter().y < 260) /*cv::waitKey(1) == 110*/) // Press "n"
            {
                //std::cout << "Iniciou a gravação" << std::endl;
                //vision.setIniciou(true);
                vision.setEstado(1);
                //aux = std::to_string(cont);

                //dataIn += aux;
                //dataIn += aux2;

                // dataIn = "resultados/teste";
                // dataIn += aux2;

                vision.saveMovement(dataIn);

                //vision.record("../Samples/sample.avi");

                while (1)
                {
                    vision.calculateTagCenter();

                    if (vision.isTargetOn())
                    {
                        vision.savePoint(vision.getCenter());
                    }

                    vision.show();
                    //vision.saveVideo();
                    //std::cout << vision.getCenter().x << " " << vision.getCenter().y << std::endl;
                    if (((10 < vision.getCenter().x && vision.getCenter().x < 50) ||
                         (590 < vision.getCenter().x && vision.getCenter().x < 630)) ||
                        ((10 < vision.getCenter().y && vision.getCenter().y < 50) ||
                         (430 < vision.getCenter().y && vision.getCenter().y < 470))) //cv::waitKey(1) == 27) //Press "Esc"
                    {

                        cont++;
                        break;
                    }
                    //cout << "salvando o centro" << endl;
                }

                vision.endSaving();
                vision.setEstado(2);
                std::cout << "Salvou!" << std::endl;
                int cont = 0, linhas, colunas = 2;
                std::string arquivoIn, arquivoOut;

                arquivoIn = "resultados/teste.csv";
                arquivoOut = "resultados/testeIn.csv";
                //arquivoIn = "data/dadosAruco/DE.csv";
                //arquivoOut = "data/dadosAruco/DEOrganizado.csv";

                // Creating an object of CSVWriter
                CSVReader reader(arquivoIn);

                std::ofstream myfile;
                myfile.open(arquivoOut);

                // Get the data from CSV File
                std::vector<std::vector<std::string>> dataList = reader.getData();

                linhas = dataList.size();

                myfile << linhas << " " << colunas << "\n";

                for (std::vector<std::string> vec : dataList)
                {
                    for (std::string data : vec)
                    {
                        myfile << data;
                        myfile << " ";
                        cont++;
                        if (cont == 2)
                        {
                            myfile << "\n";
                            cont = 0;
                        }
                    }
                }
                //std::cout << dataList.size();

                myfile.close();

                int tam = 10, iImagem, jImagem;
                int tamImagem = tam * 80; // para uma resolucao maior
                cv::Mat image(tamImagem, tamImagem, 0);
                cv::Mat imagem(tam, tam, 0);
                std::string posImagem;
                SOM som(tam);
                DataSet data;
                Sample *s;
                //Node* vencedor;
                //std::vector <Node*> vencedores; // v = find  ...

                std::string dataInSOM, imageOutVisual, imageOutTrain;

                //int imagem[tamImagem][tamImagem];

                som.loadNetworkAruco("visualization/treinamentoAruco/2500000.csv", tam);

                for (int i = 0; i < tamImagem; i++)
                {
                    for (int j = 0; j < tamImagem; j++)
                    {
                        //imagem[i][j] = 0;
                        image.at<uchar>(i, j) = 0;
                    }
                }

                for (int i = 0; i < tam; i++)
                {
                    for (int j = 0; j < tam; j++)
                    {
                        imagem.at<uchar>(i, j) = 0;
                    }
                }

                dataInSOM = "resultados/testeIn.csv";

                imageOutVisual = "resultados/visual.jpg";

                imageOutTrain = "resultados/teste.jpg";

                data.loadDataFromFile(dataInSOM);

                s = data.getRandomSample();
                som.findWinner(s, iImagem, jImagem);

                while (!(data.getRandomSample(s)))
                {
                    som.findWinner(s, iImagem, jImagem);

                    imagem.at<uchar>(iImagem, jImagem) = 255;

                    for (int i = iImagem * 80; i < (iImagem * 80 + 80); i++)
                    {
                        for (int j = jImagem * 80; j < (jImagem * 80 + 80); j++)
                        {
                            image.at<uchar>(i, j) = 255;
                        }
                    }
                }

                //cv::imshow("Nodes", image);
                cv::imwrite(imageOutVisual, image);
                cv::imwrite(imageOutTrain, imagem);
                //cv::waitKey();

                int ii = 0;
                cv::Mat imagem2 = cv::imread("resultados/teste.jpg", 0);
                int lin = imagem2.rows, col = imagem2.cols;
                int tamImg = lin * col;

                cv::Mat imagem1D(1, tamImg, CV_32FC1);
                cv::Ptr<SVM> svm;
                svm = cv::Algorithm::load<SVM>("knowledge.yml");

                for (int i = 0; i < lin; i++)
                {
                    for (int j = 0; j < col; j++)
                    {
                        imagem1D.at<float>(0, ii++) = imagem2.at<uchar>(i, j);
                    }
                }

                int predicted = svm->predict(imagem1D);

                if (predicted == 1)
                {
                    listaComandos += "\n";
                    listaComandos += identacao;
                    listaComandos += "Direita";
                    std::cout << listaComandos << std::endl;
                    programacao.push_back('d');
                }
                else if (predicted == -1)
                {
                    listaComandos += "\n";
                    listaComandos += identacao;
                    listaComandos += "Esquerda";
                    std::cout << listaComandos << std::endl;
                    programacao.push_back('e');
                }
                else if (predicted == 2)
                {
                    listaComandos += "\n";
                    listaComandos += identacao;
                    listaComandos += "Frente";
                    std::cout << listaComandos << std::endl;
                    programacao.push_back('f');
                }
                else if (predicted == -2)
                {
                    listaComandos += "\n";
                    listaComandos += identacao;
                    listaComandos += "Tras";
                    std::cout << listaComandos << std::endl;
                    programacao.push_back('t');
                }
                else if (predicted == 3)
                {
                    listaComandos += "\n";
                    listaComandos += identacao;
                    listaComandos += "Close";
                    std::cout << listaComandos << std::endl;
                    programacao.push_back('c');
                    if (contLoop == 0 && contIf == 0)
                    {
                        identacao.clear();
                        int tamArray = programacao.size();
                        char programacaoArray[tamArray];
                        for (int i = 0; i < programacao.size(); i++)
                        {
                            programacaoArray[i] = programacao.front();
                            programacao.pop_front();
                        }
                        programar(programacaoArray, tamArray);
                        programacao.clear();

                        vision.setEstado(3);
                        std::cout << std::endl
                                  << "ENVIADO" << std::endl
                                  << std::endl;
                    }
                    else
                    {
                        identacao.erase(0, 1);
                        if (blocos.top() == 'l')
                        {
                            blocos.pop();
                            contLoop--;
                        }
                        else if (blocos.top() == 'i')
                        {
                            blocos.pop();
                            contIf--;
                        }
                    }
                }
                else if (predicted == -3)
                {
                    contIf++;
                    listaComandos += "\n";
                    listaComandos += identacao;
                    listaComandos += "If";
                    std::cout << listaComandos << std::endl;
                    programacao.push_back('i');
                    identacao.insert(0, "\t");
                    blocos.push('i');
                }
                else if (predicted == 4)
                {
                    listaComandos += "\n";
                    listaComandos += identacao;
                    listaComandos += "Loop";
                    std::cout << listaComandos << std::endl;
                    programacao.push_back('l');
                    identacao.insert(0, "\t");
                    blocos.push('l');
                }
            }
        }
    }
}

void Test::programar(char CMDs[], int TAM)
{
    //char CMDs[TAM] = "AAALYAINACAAC";
    
    Program pro;
    int timeDelay = 1000;
    int velocidade = 50;
    int S[TAM];
    int SP = 0;
    for (int PC = 0; PC < TAM; PC++)
    {
        switch (CMDs[PC])
        {
        case 'd':
            std::cout << "Direita" << std::endl;
            bot.turnR(velocidade);
            delay2(timeDelay);
            break;
        case 'e':
            std::cout << "Esquerda" << std::endl;
            bot.turnL(velocidade);
            delay2(timeDelay);
            break;
        case 'f':
            std::cout << "Frente" << std::endl;
            bot.moveF(velocidade);
            delay2(timeDelay);
            break;
        case 't':
            std::cout << "Tras" << std::endl;
            bot.moveB(velocidade);
            delay2(timeDelay);
            break;
        case 'i':
            std::cout << "If" << std::endl;
            if (pro.ifIF(CMDs[PC + 1]))
            {
                PC++;
                SP++;
                S[SP] = PC;
            }
            else
            {
                pro.pulaAteC(PC, CMDs);
            }
            break;
        case 'l':
            std::cout << "Loop" << std::endl;
            if (pro.ifLOOP(CMDs[PC + 1]))
            {
                PC++;
                SP++;
                S[SP] = PC;
            }
            else
            {
                pro.pulaAteC(PC, CMDs);
            }
            break;
        case 'c':
            std::cout << "Close" << std::endl;
            if (CMDs[S[SP] - 1] == 'l')
            {
                if (pro.ifLOOP(CMDs[S[SP]]))
                {
                    PC = S[SP];
                }
                else
                {
                    SP--;
                }
            }
            else if (CMDs[S[SP] - 1] == 'i')
            {
                SP--;
            }
            break;
        default:
            cout << "EXECUTA:" << PC << endl;
            break;
        }
    }
    bot.stop();
}

Test::~Test()
{
}
