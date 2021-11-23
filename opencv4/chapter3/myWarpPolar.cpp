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

    Mat img1, img2, img3, img4;
    Point2f center(img.rows / 2.0f, img.cols / 2.0f);                                                   // 图像中心点为极坐标原点
    warpPolar(img, img1, Size(img.rows, img.cols), center, center.x, INTER_LINEAR | WARP_POLAR_LINEAR); // 正极坐标变换
    warpPolar(img1, img2, Size(img.rows, img.cols), center, center.x, INTER_LINEAR | WARP_INVERSE_MAP); // 逆极坐标变换
    warpPolar(img, img3, Size(img.rows, img.cols), center, center.x, INTER_LINEAR | WARP_POLAR_LOG);    // 正半对数极坐标变换
    warpPolar(img3, img4, Size(img.rows, img.cols), center, center.x, INTER_LINEAR | WARP_INVERSE_MAP); // 逆半对数极坐标变换
    imshow("img", img);
    imshow("img1", img1);
    imshow("img2", img2);
    imshow("img3", img3);
    imshow("img4", img4);
    waitKey(0);

    return 0;
}
