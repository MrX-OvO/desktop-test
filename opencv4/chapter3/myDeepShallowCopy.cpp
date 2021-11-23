#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

int main(int argc, char const *argv[])
{
    Mat lena = imread("../lena.png");
    Mat peppers = imread("../peppers.bmp");
    if (lena.empty() || peppers.empty())
    {
        std::cout << "请确认图像文件名称是否正确！\n";
        return -1;
    }

    Mat ROI1, ROI2, ROI2_copy, mask, lena2, lena_copy, lena_copy2;
    resize(peppers, mask, Size(200, 200));
    imshow("mask", mask);
    lena2 = lena; //浅拷贝
    // 深拷贝的两种方式
    lena.copyTo(lena_copy);
    copyTo(lena, lena_copy2, lena);

    // 两种在图像中截取ROI的方式（浅拷贝）
    Rect rect(100, 100, 200, 200);
    ROI1 = lena(rect); // 截图
    imshow("ROI1", ROI1);
    ROI2 = lena(Range(100, 300), Range(100, 300)); // 第二种截图方式
    imshow("ROI2", ROI2);
    lena(Range(100, 300), Range(100, 300)).copyTo(ROI2_copy); // 深拷贝
    mask.copyTo(ROI1);                                        // 在图像中加入部分图像
    imshow("mask effect on ROI1", ROI1);
    imshow("after add peppers.bmp to lena.png", lena);
    imshow("ROI(mask) effect on ROI2", ROI2);
    imshow("deep copy ROI2_copy", ROI2_copy);
    circle(lena, Point(120, 200), 50, Scalar(0, 255, 255)); // 绘制一个圆形（黄色）
    imshow("shallow copy lena2", lena2);
    imshow("deep copy lena_copy", lena_copy);
    imshow("deep copy lena_copy2", lena_copy2);
    imshow("circle effect on ROI1", ROI1);
    waitKey(0);

    return 0;
}
