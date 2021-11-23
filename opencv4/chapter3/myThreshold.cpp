#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;

int main(int argc, char const *argv[])
{
    Mat img = imread("../lena.png");
    if (img.empty())
    {
        std::cout << "请确认图像文件名称是否正确！\n";
        return -1;
    }

    Mat gray;
    cvtColor(img, gray, COLOR_RGB2GRAY);
    Mat img_B, img_B_V, gray_B, gray_B_V, gray_T, gray_T_V, gray_TRUNC;
    // 彩色图像二值化
    threshold(img, img_B, 125, 255, THRESH_BINARY);
    threshold(img, img_B_V, 125, 255, THRESH_BINARY_INV);
    imshow("img_B", img_B);
    imshow("img_B_V", img_B_V);
    // 灰度图像BINARY二值化
    threshold(gray, gray_B, 125, 255, THRESH_BINARY);
    threshold(gray, gray_B_V, 125, 255, THRESH_BINARY_INV);
    imshow("gray_B", gray_B);
    imshow("gray_B_V", gray_B_V);
    // 灰度图像TOZERO二值化
    threshold(gray, gray_B, 125, 255, THRESH_BINARY);
    threshold(gray, gray_B_V, 125, 255, THRESH_BINARY_INV);
    imshow("gray_B", gray_B);
    imshow("gray_B_V", gray_B_V);
    //灰度图像TRUNC二值化
    threshold(gray, gray_T, 125, 255, THRESH_TOZERO);
    threshold(gray, gray_T_V, 125, 255, THRESH_TOZERO_INV);
    imshow("gray_T", gray_T);
    imshow("gray_T_V", gray_T_V);
    //灰度图像大律法和三角形法二值化
    Mat img_Thr = imread("../peppers.bmp", IMREAD_GRAYSCALE);
    Mat img_Thr_O, img_Thr_T;
    threshold(img_Thr, img_Thr_O, 100, 255, THRESH_BINARY);
    threshold(img_Thr, img_Thr_T, 125, 255, THRESH_BINARY_INV);
    imshow("img_Thr_O", img_Thr_O);
    imshow("img_Thr_T", img_Thr_T);
    // 灰度图像自适应二值化
    Mat adaptive_Mean, adaptive_Gauss;
    adaptiveThreshold(img_Thr, adaptive_Mean, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 55, 0);
    adaptiveThreshold(img_Thr, adaptive_Gauss, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 55, 0);
    imshow("adaptive_Mean", adaptive_Mean);
    imshow("adaptive_Gauss", adaptive_Gauss);
    waitKey(0);

    return 0;
}
