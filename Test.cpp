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
//#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>

using namespace cv::ml;

Test::Test()
{
}

Test::Test(const Test &orig)
{
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
}

void Test::organizeCSVAruco()
{
    int cont = 0, linhas, colunas = 2;
    std::string arquivoIn, arquivoOut, aux, aux2;
    aux2 = ".csv";

    for (int i = 1; i < 21; i++)
    {
        aux = std::to_string(i);
        arquivoIn = "data/dadosAruco/Tras/tras";
        arquivoIn += aux;
        arquivoIn += aux2;

        arquivoOut = "data/dadosAruco/DEFTNew/tras";
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
    std::string fileData = "data/dadosAruco/DEFTOrganizado.csv";

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
        if (i % 10000 == 0)
        {
            som.printNodes();
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

    for (int i = 1; i < 21; i++)
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
        dataIn = "data/dadosAruco/DEFTNew/frente";
        dataIn += aux;
        dataIn += aux2;

        imageOutVisual = "resultadosSom/visualizar/frenteVisual";
        imageOutVisual += aux;
        imageOutVisual += aux3;

        imageOutTrain = "resultadosSom/treinar/frenteTrain";
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
    int qntImg = 80, tamImg = lin * col;
    int labels[qntImg];
    std::vector<cv::Mat> imagem(qntImg);

    std::string dataIn, aux, aux2;
    aux2 = ".jpg";

    for (int i = 1; i < qntImg + 1; i++)
    {
        if (i < 21)
        {
            aux = std::to_string(i);
            dataIn = "resultadosSom/treinar/direitaTrain";
            dataIn += aux;
            dataIn += aux2;
            imagem[i - 1] = cv::imread(dataIn, 0);
            labels[i - 1] = 1;
            std::cout << dataIn << std::endl;
        }
        else if (i < 41)
        {
            aux = std::to_string(i - 20);
            dataIn = "resultadosSom/treinar/esquerdaTrain";
            dataIn += aux;
            dataIn += aux2;
            imagem[i - 1] = cv::imread(dataIn, 0);
            labels[i - 1] = -1;
            std::cout << dataIn << std::endl;
        }
        else if (i < 61)
        {
            aux = std::to_string(i - 40);
            dataIn = "resultadosSom/treinar/frenteTrain";
            dataIn += aux;
            dataIn += aux2;
            imagem[i - 1] = cv::imread(dataIn, 0);
            labels[i - 1] = 2;
        }
        else if (i < 81)
        {
            aux = std::to_string(i - 60);
            dataIn = "resultadosSom/treinar/trasTrain";
            dataIn += aux;
            dataIn += aux2;
            imagem[i - 1] = cv::imread(dataIn, 0);
            labels[i - 1] = -2;
        }
    }

    //int ii = 0;
    cv::Mat matImage(qntImg, tamImg, CV_32FC1);
    for (int k = 0; k < qntImg; k++)
    {
        for (int i = 0; i < lin; i++)
        {
            for (int j = 0; j < col; j++)
            {
                matImage.at<float>(k, 0) = imagem[k].at<uchar>(0, 0);
            }
        }
        //ii = 0;
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
    svm->setGamma(8);
    svm->setDegree(3);
    svm->setC(0.05);
    svm->setCoef0(0.6);
    svm->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER, 100000, 1e-6));
    //! [init]
    //! [train]
    svm->train(matImage, ROW_SAMPLE, labelsMat);

    // store its knowledge in a yaml file
    svm->save("knowledge.yml");
    //! [train]
}

void Test::loadSVM2()
{
    int ii = 0;
    cv::Mat imagem;
    imagem = cv::imread("testar/direitaTrain10.jpg", 0);
    //imagem[1] = cv::imread("direitaTrain2.jpg", 0);
    //imagem[2] = cv::imread("frenteTrain4.jpg", 0);
    int lin = 10, col = 10;
    int tamImg = lin * col;

    std::string dataIn, aux, aux2;
    aux2 = ".jpg";

    cv::Mat imagem1D(1, tamImg, CV_32FC1);
    cv::Ptr<SVM> svm;
    svm = cv::Algorithm::load<SVM>("knowledge.yml");

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

    /*if (predicted == 1)
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
                      << std::endl;*/
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

    std::string dataIn, aux, aux2;
    //aux2 = ".csv";
    int cont = 1;

    while (1)
    {
        if (cv::waitKey(1) == 110)
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
                if (cv::waitKey(1) == 27)
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

            som.loadNetworkAruco("visualization/treinamentoAruco/15000.csv", tam);

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

            std::cout << predicted << std::endl;

            if (predicted == 1)
                std::cout << std::endl
                          << "Esquerda" << std::endl
                          << std::endl;
            else if (predicted == -1)
                std::cout << std::endl
                          << "Direita" << std::endl
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
        }
        //cout << "Esperando o 'n'!" << endl;
    }
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
            dataIn = "data/dadosAruco/Frente/frente";
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
                    std::cout << cont << std::endl;
                    break;
                }
            }
            vision.endSaving();
            std::cout << "Salvou!" << std::endl;
        }
    }
}

Test::~Test()
{
}
