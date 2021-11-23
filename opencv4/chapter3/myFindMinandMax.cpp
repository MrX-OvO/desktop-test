#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;

int main(int argc, char const *argv[])
{
    float farr[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Mat img = Mat(3, 4, CV_32FC1, farr);  // 单通道
    Mat img2 = Mat(2, 3, CV_32FC2, farr); // 多（2）通道
    double minVal, maxVal;                // 矩阵中最小值和最大值
    Point minIdx, maxIdx;                 // 矩阵中最小值和最大值的位置

    // 寻找单通道矩阵的中的最值
    minMaxLoc(img, &minVal, &maxVal, &minIdx, &maxIdx);
    std::cout << "img minVal = " << minVal << ", pos = " << minIdx << std::endl;
    std::cout << "img maxVal = " << maxVal << ", pos = " << maxIdx << std::endl;
    // 寻找多通道矩阵的中的最值
    Mat img2_re = img2.reshape(1); // 将多通道转为单通道
    minMaxLoc(img2_re, &minVal, &maxVal, &minIdx, &maxIdx);
    std::cout << "img2 minVal = " << minVal << ", pos = " << minIdx << std::endl;
    std::cout << "img2 maxVal = " << maxVal << ", pos = " << maxIdx << std::endl;

    return 0;
}
