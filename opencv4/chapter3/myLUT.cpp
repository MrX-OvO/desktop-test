#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;

int main(int argc, char const *argv[])
{
    // LUT第一层
    uchar lutFirst[256];
    for (size_t i = 0; i < 256; ++i)
    {
        if (i < 100)
            lutFirst[i] = 0;
        else if (i > 100 && i <= 200)
            lutFirst[i] = 100;
        else
            lutFirst[i] = 255;
    }
    Mat lutOne(1, 256, CV_8UC1, lutFirst);

    // LUT第二层
    uchar lutSecond[256];
    for (size_t i = 0; i < 256; ++i)
    {
        if (i < 100)
            lutSecond[i] = 0;
        else if (i > 100 && i <= 150)
            lutSecond[i] = 100;
        else if (i > 150 && i <= 200)
            lutSecond[i] = 150;
        else
            lutSecond[i] = 255;
    }
    Mat lutTwo(1, 256, CV_8UC1, lutSecond);

    // LUT第三层
    uchar lutThrid[256];
    for (size_t i = 0; i < 256; ++i)
    {
        if (i < 100)
            lutThrid[i] = 0;
        else if (i > 100 && i <= 200)
            lutThrid[i] = 200;
        else
            lutThrid[i] = 255;
    }
    Mat lutThree(1, 256, CV_8UC1, lutThrid);

    // 拥有三通道的LUT矩阵
    std::vector<Mat> mergeMats;
    mergeMats.push_back(lutOne);
    mergeMats.push_back(lutTwo);
    mergeMats.push_back(lutThree);
    Mat mergeMatsLUTThr;
    merge(mergeMats, mergeMatsLUTThr);

    Mat img = imread("../lena.png");
    if (img.empty())
    {
        std::cout << "请确认图像文件名称是否正确！\n";
        return -1;
    }

    Mat gray, out0, out1, out2, out3;
    cvtColor(img, gray, COLOR_RGB2GRAY);
    LUT(gray, lutOne, out1);
    LUT(img, lutTwo, out2);
    LUT(img, lutThree, out3);
    LUT(img, mergeMatsLUTThr, out0);
    imshow("out0", out0);
    imshow("out1", out1);
    imshow("out2", out2);
    imshow("out3", out3);
    waitKey(0);

    return 0;
}
