#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;

int main(int argc, char const *argv[])
{
    float a[12] = {1, 2, 3.3, 4, 5, 6, 7.2, 8, 9, 10.24, 11, 12};
    float b[12] = {1.5, 2, 3, 4, 5, 6.3, 7.6, 8, 9, 10.2, 11, 12.1};
    Mat imga = Mat(3, 4, CV_32FC1, a);
    Mat imgb = Mat(3, 4, CV_32FC1, b);
    Mat imgas = Mat(3, 2, CV_32FC2, a);
    Mat imgbs = Mat(3, 2, CV_32FC2, b);

    // 对两个单通道矩阵进行比较运算
    Mat myMin, myMax;
    min(imga, imgb, myMin);
    max(imga, imgb, myMax);
    std::cout << "对两个单通道矩阵进行比较运算\n"
              << "myMin = "
              << myMin << std::endl
              << "myMax = " << myMax << std::endl;

    // 对两个多通道矩阵进行比较运算
    Mat myMins, myMaxs;
    min(imgas, imgbs, myMins);
    max(imgas, imgbs, myMaxs);
    std::cout << "对两个多通道矩阵进行比较运算\n"
              << "myMins = " << myMins << std::endl
              << "myMaxs = " << myMaxs << std::endl;

    // 对两幅彩色图像进行比较运算
    Mat img0 = imread("../lena.png");
    Mat img1 = imread("../peppers.bmp");
    if (img0.empty() || img1.empty())
    {
        std::cout << "请确认图像文件名称是否正确！\n";
        return -1;
    }
    Mat comMin, comMax;
    min(img0, img1, comMin);
    max(img0, img1, comMax);
    imshow("comMin", comMin);
    imshow("comMax", comMax);

    // 与掩模进行比较运算
    Mat src1 = Mat::zeros(Size(512, 512), CV_8UC3);
    Mat src2 = Mat(Size(512, 512), CV_8UC3, Scalar(0, 0, 255)); // 生成一个显示红色通道的低通掩模
    Rect rect(100, 100, 300, 300);
    src1(rect) = Scalar(255, 255, 255); // 生成一个低通300x300的掩模
    Mat comsrc1, comsrc2;
    min(img0, src1, comsrc1);
    min(img0, src2, comsrc2);
    imshow("comsrc1", comsrc1);
    imshow("comsrc2", comsrc2);

    // 对两幅灰度图像进行比较运算
    Mat img0G, img1G, comMinG, comMaxG;
    cvtColor(img0, img0G, COLOR_RGB2GRAY);
    cvtColor(img1, img1G, COLOR_RGB2GRAY);
    min(img0G, img1G, comMinG);
    max(img0G, img1G, comMaxG);
    imshow("comMinG", comMinG);
    imshow("comMaxG", comMaxG);
    waitKey(0);

    return 0;
}
