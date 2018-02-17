//
// Created by ed_grolsh on 24.05.17.
//

#include <iostream>
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv/ml.h>
#include "SVM_test.hpp"
using std::cout;
using std::cin;
using std::endl;

void SVM_test::loadTrainTestLabel(std::vector<cv::Mat> &trainCells, std::vector<cv::Mat> &testCells,
                             std::vector<int> &trainLabels, std::vector<int> &testLabels) {
    std::string pathName = "0.jpg";
    int ImgCount = 0;
    int number_of_photos_with_face = 10;
    int number_of_photos_without_face = 10;
    for(int i = 0; i < (number_of_photos_with_face + number_of_photos_without_face); i++) {
        cv::Mat img = cv::imread(pathName,CV_LOAD_IMAGE_GRAYSCALE);
        cv::Mat digitImg = img.clone();
        if (i <= number_of_photos_with_face)
            if (ImgCount % 4 == 0) {
                trainCells.push_back(digitImg);
            } else {
                testCells.push_back(digitImg);
            }
        ImgCount++;
        pathName.replace(0, 1, std::to_string(i + 1));
    }

    cout << "Image Count : " << ImgCount << endl;
    int digitClassNumber = 0;
    int number_photo_with_face_test = number_of_photos_with_face / 4;
    for (int z=0; z < (number_of_photos_with_face - number_photo_with_face_test); z++){
        trainLabels.push_back(digitClassNumber);
    }
    digitClassNumber++;
    for (int z=0; z < trainCells.size(); z++){
        trainLabels.push_back(digitClassNumber);
    }
    //разобраться с тестами
    digitClassNumber = 0;
    for(int z=0; z < number_photo_with_face_test; z++){
        testLabels.push_back(digitClassNumber);
    }
    digitClassNumber++;
    for(int z=0; z < testCells.size(); z++){
        testLabels.push_back(digitClassNumber);
    }
}

void SVM_test::CreateTrainTestHOG() {
    int number_of_HOG_attribute = trainCells[0].at<cv::Mat>(0, 0).total();
    for(int k = 0; k < trainCells.size(); k++){
        std::vector<int> descriptors;
        for (size_t i = 0; i < trainCells[0].rows; i++)
            for (size_t j = 0; j < trainCells[0].cols; j++)
                for (size_t m = 0; m < number_of_HOG_attribute; m++)
                descriptors.push_back(trainCells[k].at<int>(i, j, m));//достаем одно значение инта

        ;
        trainHOG.push_back(descriptors);
    }

    for(int k = 0; k < testCells.size(); k++){
        std::vector<int> descriptors;
        for (size_t i = 0; i < testCells[0].rows; i++)
            for (size_t j = 0; j < testCells[0].cols; j++)
                for (size_t m = 0; m < number_of_HOG_attribute; m++)
                    descriptors.push_back(testCells[k].at<int>(i, j, m));
        testHOG.push_back(descriptors);
    }
}

void SVM_test::SVM_training() {
    CreateTrainTestHOG();
    int descriptor_size = trainHOG[0].size();
    cout << "Descriptor Size : " << descriptor_size << endl;
    ConvertVectortoMatrix();
    SVMtrain();
}

void SVM_test::getSVMParams(cv::ml::SVM *svm) {
    cout << "Kernel type     : " << svm->getKernelType() << endl;
    cout << "Type            : " << svm->getType() << endl;
    cout << "C               : " << svm->getC() << endl;
    cout << "Degree          : " << svm->getDegree() << endl;
    cout << "Nu              : " << svm->getNu() << endl;
    cout << "Gamma           : " << svm->getGamma() << endl;
}

void SVM_test::SVMtrain() {
    Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
    svm->setGamma(0.50625);
    svm->setC(12.5);
    svm->setKernel(cv::ml::SVM::RBF);
    svm->setType(cv::ml::SVM::C_SVC);
    Ptr<cv::ml::TrainData> td = cv::ml::TrainData::create(trainMat, cv::ml::ROW_SAMPLE, trainLabels);
    svm->train(td);
    //svm->trainAuto(td);
    svm->save("model4.yml");
    svm->predict(testMat, testResponse);
    getSVMParams(svm);
}

void SVM_test::ConvertVectortoMatrix()
{
    int descriptor_size = trainHOG[0].size();

    for(int i = 0;i<trainHOG.size();i++){
        for(int j = 0;j<descriptor_size;j++){
            trainMat.at<int>(i,j) = trainHOG[i][j];
        }
    }
    for(int i = 0;i<testHOG.size();i++){
        for(int j = 0;j<descriptor_size;j++){
            testMat.at<int>(i,j) = testHOG[i][j];
        }
    }

}





