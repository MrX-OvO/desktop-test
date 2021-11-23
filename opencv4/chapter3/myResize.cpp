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

    Mat smallImg, bigImg0, bigImg1, bigImg2;
    resize(img, smallImg, Size(15, 15), 0, 0, INTER_AREA);
    resize(smallImg, bigImg0, Size(30, 30), 0, 0, INTER_NEAREST);
    resize(smallImg, bigImg1, Size(30, 30), 0, 0, INTER_LINEAR);
    resize(smallImg, bigImg2, Size(30, 30), 0, 0, INTER_CUBIC);
    namedWindow("smallImg", WINDOW_NORMAL); // 图像尺寸太小，需要设置可以调节窗口大小的标志
    imshow("smallImg", smallImg);
    namedWindow("bigImg0", WINDOW_NORMAL);
    imshow("bigImg0", bigImg0);
    namedWindow("bigImg1", WINDOW_NORMAL);
    imshow("bigImg1", bigImg1);
    namedWindow("bigImg2", WINDOW_NORMAL);
    imshow("bigImg2", bigImg2);
    waitKey(0);

    return 0;
}
