#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;

int main(int argc, char const *argv[])
{
    float farr[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Mat img = Mat(3, 4, CV_32FC1, farr);  // 单通道
    Mat img2 = Mat(2, 3, CV_32FC2, farr); // 多（2）通道

    std::cout << "/* 用mean求图像的平均值 */\n";
    Scalar myMean = mean(img);
    std::cout << "img平均值 = " << myMean << std::endl;
    myMean = mean(img2);
    std::cout << "img2平均值 = " << myMean << std::endl
              << "img2第一个通道的平均值 = " << myMean[0] << std::endl
              << "img2第二个通道的平均值 = " << myMean[1] << std::endl
              << std::endl;

    std::cout << "/* 用meanStdDev求图像的平均值 */\n";
    Mat myMeanMat, myStdDevMat;
    meanStdDev(img, myMeanMat, myStdDevMat);
    std::cout << "img平均值 = " << myMeanMat << std::endl
              << "img标准差 = " << myStdDevMat << std::endl;
    meanStdDev(img2, myMeanMat, myStdDevMat);
    std::cout << "img2平均值 = " << myMeanMat << std::endl
              << "img2标准差 = " << myStdDevMat << std::endl;

    return 0;
}
