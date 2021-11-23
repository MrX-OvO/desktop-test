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

    // 创建两个黑白图像
    Mat img0 = Mat::zeros(200, 200, CV_8UC1);
    Mat img1 = Mat::zeros(200, 200, CV_8UC1);
    Rect rect0(50, 50, 100, 100);
    img0(rect0) = Scalar(255);
    Rect rect1(100, 100, 100, 100);
    img1(rect1) = Scalar(255);
    imshow("img0", img0);
    imshow("img1", img1);

    // 进行逻辑运算
    Mat myAnd, myOr, myXor, myNot0, myNot1, imgNot;
    bitwise_and(img0, img1, myAnd);
    bitwise_or(img0, img1, myOr);
    bitwise_xor(img0, img1, myXor);
    bitwise_not(img0, myNot0);
    bitwise_not(img1, myNot1);
    bitwise_not(img, imgNot);
    imshow("myAnd", myAnd);
    imshow("myOr", myOr);
    imshow("myXor", myXor);
    imshow("myNot0", myNot0);
    imshow("myNot1", myNot1);
    imshow("imgNot", imgNot);
    waitKey(0);

    return 0;
}
