#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

int main(int argc, char const *argv[])
{
    Mat img = imread("../lena.png");
    if (img.empty())
    {
        std::cout << "请确认图像文件名称是否正确！\n";
        return -1;
    }

    Mat gray, HSV, YUV, Lab, img32;
    img.convertTo(img32, CV_32F, 1.0 / 255); // 将CV_8U类型转换成CV_32F类型
    cvtColor(img32, gray, COLOR_RGB2GRAY);
    cvtColor(img32, HSV, COLOR_RGB2HSV);
    cvtColor(img32, YUV, COLOR_RGB2YUV);
    cvtColor(img32, Lab, COLOR_RGB2Lab);
    imshow("origin", img);
    imshow("gray", gray);
    imshow("HSV", HSV);
    imshow("YUV", YUV);
    imshow("Lab", Lab);
    waitKey(0);

    return 0;
}
