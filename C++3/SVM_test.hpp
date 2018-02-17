//
// Created by ed_grolsh on 24.05.17.
//

#ifndef C_3_SVM_TEST_HPP
#define C_3_SVM_TEST_HPP


#include <vector>
#include <opencv2/core/mat.hpp>
#ifdef USE_OPENCV_3
#include <iostream>
   #include <opencv2/highgui.hpp>
   #include <opencv2/imgproc.hpp>
   #include "opencv2/objdetect.hpp"
   #include <opencv2/ml.hpp>
#endif

#ifdef USE_OPENCV_2
#include <cv.h>
   #include <highgui.h>
   #include <opencv2/ml/ml.hpp>
#endif

#include <iostream>


#ifdef USE_OPENCV_3
using namespace cv::ml;
#endif
using namespace cv;
using namespace std;

class SVM_test {
public:
    void SVM_training();
    void loadTrainTestLabel(std::vector<cv::Mat> &trainCells, std::vector<cv::Mat> &testCells,
                            std::vector<int> &trainLabels, std::vector<int> &testLabels);

private:
    std::vector<cv::Mat> trainCells;
    std::vector<cv::Mat> testCells;
    std::vector<int> trainLabels;
    std::vector<int> testLabels;
    std::vector<std::vector<int>> trainHOG;
    std::vector<std::vector<int>> testHOG;
    cv::Mat trainMat(12, 9, CV_32SC1);
    cv::Mat testMat(12, 9 , CV_32SC1);
    cv::Mat testResponse;

    void getSVMParams(cv::ml::SVM *svm);
    void CreateTrainTestHOG();
    void SVMtrain();
    void ConvertVectortoMatrix();

};


#endif //C_3_SVM_TEST_HPP
