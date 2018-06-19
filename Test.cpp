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

void Test::organizeCSVAruco()
{
    int cont = 0, linhas, colunas = 2;
    std::string arquivoIn, arquivoOut, aux, aux2;
    aux2 = ".csv";

    for (int i = 1; i < 16; i++)
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

    int iterations = 150;

    // Execute many iterations
    int i = 0;
    som.printNodes();
    while (i < (iterations))
    {
        som.executeOneIt();
        i++;
        som.printNodes();

        som.saveNodes("visualization/treinamentoAruco/", "i,j,x,y", false);
    }

    //som.printNodes();
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

    som.loadNetworkAruco("visualization/treinamentoAruco/150.csv", tam);

    for (int i = 1; i < 16; i++)
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
        dataIn = "data/dadosAruco/DEFTNew/tras";
        dataIn += aux;
        dataIn += aux2;

        imageOutVisual = "resultadosSom/visualizar/trasVisual";
        imageOutVisual += aux;
        imageOutVisual += aux3;

        imageOutTrain = "resultadosSom/treinar/trasTrain";
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
    int qntImg = 60, tamImg = lin * col;
    int labels[qntImg];
    std::vector<cv::Mat> imagem(qntImg);

    std::string dataIn, aux, aux2;
    aux2 = ".jpg";

    for (int i = 1; i < 61; i++)
    {
        if (i < 16)
        {
            aux = std::to_string(i);
            dataIn = "resultadosSom/treinar/direitaTrain";
            dataIn += aux;
            dataIn += aux2;
            imagem[i - 1] = cv::imread(dataIn, 0);
            labels[i - 1] = 2;
        }
        else if (i < 31)
        {
            aux = std::to_string(i - 15);
            dataIn = "resultadosSom/treinar/esquerdaTrain";
            dataIn += aux;
            dataIn += aux2;
            imagem[i - 1] = cv::imread(dataIn, 0);
            labels[i - 1] = -2;
        }
        else if (i < 46)
        {
            aux = std::to_string(i - 30);
            dataIn = "resultadosSom/treinar/frenteTrain";
            dataIn += aux;
            dataIn += aux2;
            imagem[i - 1] = cv::imread(dataIn, 0);
            labels[i - 1] = 1;
        }
        else
        {
            aux = std::to_string(i - 45);
            dataIn = "resultadosSom/treinar/trasTrain";
            dataIn += aux;
            dataIn += aux2;
            imagem[i - 1] = cv::imread(dataIn, 0);
            labels[i - 1] = -1;
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
                matImage.at<float>(k, 0) = imagem[k].at<uchar>(0, 0);
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
    svm->setKernel(SVM::LINEAR);
    svm->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER, 100, 1e-6));
    //! [init]
    //! [train]
    svm->train(matImage, ROW_SAMPLE, labelsMat);

    // store its knowledge in a yaml file
    svm->save("knowledge.yml");
    //! [train]
}

void Test::loadSVM()
{
    int ii = 0;
    cv::Mat imagem = cv::imread("teste.jpg", 0);
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
}

Test::~Test()
{
}
