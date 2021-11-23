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

    Mat HSV;
    cvtColor(img, HSV, COLOR_BGR2HSV);
    Mat imgs0, imgs1, imgs2;       // 用于存放数组类型的结果
    Mat imgv0, imgv1, imgv2;       // 用于存放vector类型的结果
    Mat result0, result1, result2; // 多通道合并结果

    Mat imgs[3]; // 数组类型
    split(img, imgs);
    imgs0 = imgs[0];
    imgs1 = imgs[1];
    imgs2 = imgs[2];
    imshow("RGB-B Channel", imgs0); // 显示分离后的B通道的像素值
    imshow("RGB-G Channel", imgs1); // 显示分离后的G通道的像素值
    imshow("RGB-R Channel", imgs2); // 显示分离后的R通道的像素值
    //imgs[2] = img;               // 将数组中的图像通道数变成不一致
    //merge(imgs, 3, result0);
    //imshow("result0", result0);
    Mat zero = Mat::zeros(img.rows, img.cols, CV_8UC1);
    imgs[0] = zero;
    imgs[2] = zero;
    merge(imgs, 3, result1);
    imshow("result1", result1);

    std::vector<Mat> imgv; // vector类型
    split(HSV, imgv);
    imgv0 = imgv.at(0);
    imgv1 = imgv.at(1);
    imgv2 = imgv.at(2);
    imshow("HSV-H Channel", imgs0); // 显示分离后的B通道的像素值
    imshow("HSV-S Channel", imgs1); // 显示分离后的G通道的像素值
    imshow("HSV-V Channel", imgs2); // 显示分离后的R通道的像素值
    //imgv.push_back(HSV);         // 将vector中的图像通道数变成不一致
    merge(imgv, result2);
    imshow("result2", result2);
    waitKey(0);

    return 0;
}